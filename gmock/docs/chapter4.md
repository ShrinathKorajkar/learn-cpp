Chapter 4 - Controlling Threads
===============================

Key Concepts
------------

* Waiting for an asynchronous event
* Invoke from mock objects
* Testing for non-events
* Prompt termination
* Self-pipe

Waiting for an asynchronous event
---------------------------------

Asynchronous code presents a fresh challenge.  No longer can we call a function and
expect results in the very next line of code.  The results we're anticipating may not
be available until some undetermined amount of time in the future.  Non-deterministic
unit tests do more harm than good as they erode confidence in the tests and generate
animosity towards unit tests.

#### The problem

Let's first look at what would happen if we didn't do anything special.

A test for a class that dispatches events to listeners may look something like this:

```c++
TEST_F(StateMachineEvents, Notification)
{
    bool called = false;
    auto listener = [&called](StateMachine::State newState){ called = true; };
    m_stateMachine.subscribe(listener);
    
    m_stateMachine.changeState(StateMachine::State::Busy);
    
    EXPECT_THAT(called, Eq(true));
}
```

The above test works provided that StateMachine notifies all subscribers before
returning from `changeState`.

However, if StateMachine is implemented with threads so that subscribers are notified
in the background, then we get inconsistent behaviour.  Depending on the thread
scheduling on the system at the time the test _may_ succeed, or it _may_ fail:

```
[ RUN      ] StateMachineEvents.Notification
../../statemachine/src/test/test_statemachine.cpp:27: Failure
Value of: called
Expected: is equal to true
  Actual: false (of type bool)
[  FAILED  ] StateMachineEvents.Notification (0 ms)
```

More effort is required to have a reliable test in the face of async behaviour.

#### Blind waiting

A common reaction after realizing that the failure is due to the test validating the
callback too early is to put a sleep in the test so that the background thread has a
chance to notify the callback before we test for it.

```c++
TEST_F(StateMachineEvents, Notification)
{
    bool called = false;
    auto listener = [&called](StateMachine::State newState){ called = true; };
    m_stateMachine.subscribe(listener);
    
    m_stateMachine.changeState(StateMachine::State::Busy);
    
    this_thread::sleep_for(chrono::milliseconds(1));
    EXPECT_THAT(called, Eq(true));
}
```

This approach to synchronization relies on guessing how long the sleep should be.  If the
sleep is too short, then the test will _still_ fail.  Some machines are slower than others
and require a longer sleep in order to not produce a false failure.  So the _Works On My
Machine_ measurement isn't sufficient.  Some instrumented builds execute more slowly than
optimized builds.  AddressSanitizer builds can be expected to run at a 2x slowdown.  Any
sleep would need to be twice as long to compensate.  ThreadSanitizer builds can be expected
to run at a 10x slowdown.  Execution under Valgrind may legitimately run at a 100x slowdown
depending on what the code is doing.  Any sleep would need to be 100x as long to compensate.

A sleep will force a lower bound on the duration of the test.  The test will never run
in less time.

Sleep is not a viable synchronization strategy.  ThreadSanitizer will even call you out for
it (note the *As if synchronnized via sleep* -- it is insufficient to avoid the data race):

```
WARNING: ThreadSanitizer: data race (pid=25664)
  Read of size 1 at 0x7ffc115ab367 by main thread:
    #0 bool testing::internal::AnyEq::operator()<bool, bool>(bool const&, bool const&) const /build/work/13dc77d801f55880/build/tsan/deps/GoogleTest/1.8.0/googlemock/include/gmock/gmock-matchers.h:204:58 (test_statemachine+0x000000516d5b)
    <skip>
    #16 main /build/work/13dc77d801f55880/build/tsan/deps/GoogleTest/1.8.0/googlemock/src/gmock_main.cc:53:10 (test_statemachine+0x000000551936)

  Previous write of size 1 at 0x7ffc115ab367 by thread T1 (mutexes: write M33):
    #0 StateMachineEvents_Notification_Test::TestBody()::$_0::operator()(StateMachine::State) const /build/work/13dc77d801f55880/statemachine/src/test/test_statemachine.cpp:21:69 (test_statemachine+0x000000514850)
    <skip>
    #8 <null> <null> (libstdc++.so.6+0x0000000b8c7f)

  As if synchronized via sleep:
    #0 nanosleep <null> (test_statemachine+0x0000004ae85a)
    <skip>
    #13 main /build/work/13dc77d801f55880/build/tsan/deps/GoogleTest/1.8.0/googlemock/src/gmock_main.cc:53:10 (test_statemachine+0x000000551936)

  Location is stack of main thread.

  Mutex M33 (0x7d3c0000ee90) created at:
    #0 pthread_mutex_lock <null> (test_statemachine+0x00000049af97)
    <skip>
    #16 main /build/work/13dc77d801f55880/build/tsan/deps/GoogleTest/1.8.0/googlemock/src/gmock_main.cc:53:10 (test_statemachine+0x000000551936)

  Thread T1 (tid=25670, running) created by main thread at:
    #0 pthread_create <null> (test_statemachine+0x00000048546b)
    <skip>
    #15 main /build/work/13dc77d801f55880/build/tsan/deps/GoogleTest/1.8.0/googlemock/src/gmock_main.cc:53:10 (test_statemachine+0x000000551936)

SUMMARY: ThreadSanitizer: data race /build/work/13dc77d801f55880/build/tsan/deps/GoogleTest/1.8.0/googlemock/include/gmock/gmock-matchers.h:204:58 in bool testing::internal::AnyEq::operator()<bool, bool>(bool const&, bool const&) const
```

#### Test duration

What is a reasonable duration for a unit test?

Few people would argue for an hour-long test to be called a unit test and executed on every build.
If we execute the tests frequently (such as on every build), then they must complete in much
less time.

What if we target 1 second?  In human terms this is a very short period of time.  Few people
mind a wait of an extra second.  Especially if it brings value that saves a much longer amount
of time.  What does that look like when we write multiple unit tests?  The PCoIP Agent codebase
currently contains roughly 2500 unit tests.  If each one took a mere 1s, then every build
would consume an additional 40 minutes just to execute the unit tests.

Andrew c.2018 has been using a threshold of 10 milliseconds and thus far has not needed to adjust
that value.  Any unit test that exceeds that threshold has had room for improvement that has
decreased the execution time.  Note that this threshold is measured on Release builds on Linux.
Windows builds are sometimes less consistent in its execution times.  Sanitizer and Valgrind
runs are consistently slower.  It's natural for them to exceed the 10ms threshold.

Modern CPUs can do a mind boggling amount of work in a single millisecond.  Unit tests should be
testing a single thing; a budget of 10ms is very reasonable.  Componenet or Integration tests
may bring up more of the system and have external delays.  These may still leverage GTest and
GMock but would not run on every build and thus may have a larger time budget.

#### Synchronization

Neither GTest nor GMock provide tools to simplify synchronization of threads.  Fortunately C++11
has made it far easier than previously.

To control our test execution in a deterministic manner we must suspend the validation in our
test _just long enough_ for the other thread(s) to do their work and then we want to proceed
without any further delay.  We can use C++11's `std::mutex` and `std::condition_variable` to
do exactly this.

```c++
TEST_F(StateMachineEvents, Notification)
{
    mutex flagMutex;
    bool called = false;
    condition_variable flagCv;

    auto listener = [&flagMutex, &called, &flagCv](StateMachine::State newState) {
        {
            lock_guard<mutex> _(flagMutex);
            called = true;
        }
        flagCv.notify_all();
    };
    m_stateMachine.subscribe(listener);

    m_stateMachine.changeState(StateMachine::State::Busy);

    unique_lock<mutex> lock(flagMutex);
    flagCv.wait_for(lock, chrono::seconds(2), [&called] { return called; });
    EXPECT_THAT(called, Eq(true));
}
```

NOTE: If `wait_for` is used, the timeout must be long enough to acommodate the slowest machine
running the slowest variant (typically Valgrind) or the test will be unreliable as it will
sometimes report a false failure.  Andrew c.2018 favours a timeout in the order of seconds within
test code and no timeout at all (infinite) in product code.

The wait on the condition_variable has a distinct advantage over a blind sleep -- it doesn't
wait any longer than absolutely necessary.  While the worst-case scenario (typically a slow or
under load machine running tests under Valgrind) may still be in the order of seconds, the
common, measurable, case is still responsive while maintaining a deterministic behaviour:

```
[ RUN      ] StateMachineEvents.Notification
[       OK ] StateMachineEvents.Notification (0 ms)
```

The above test has already grown out of control.  While the flag and associated mutex and
condition_variable can be moved to the fixture, the fixture may quickly become noisy if
multiple independent flags are required at some point.  Not to mention the violation of the
Single Responsibility Principle.  We can abstract away this synchronization flag:

```c++
class SyncFlag
{
public:
    void set()
    {
        {
            std::lock_guard<std::mutex> _(m_mutex);
            m_flag = true;
        }
        m_cv.notify_all();
    }

    void wait()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait_for(lock, chrono::seconds(2), [this] { return m_flag; });
    }

    bool isSet() const
    {
        return m_flag;
    }

private:
    std::mutex m_mutex;
    bool m_flag = false;
    std::condition_variable m_cv;
};
```

The test fixture needs only one line for each flag and the tests can focus on what makes
the test interesting.

```c++
TEST_F(StateMachineEvents, Notification)
{
    auto listener = [this](StateMachine::State newState) { m_flag.set(); };
    m_stateMachine.subscribe(listener);

    m_stateMachine.changeState(StateMachine::State::Busy);

    m_flag.wait();
    EXPECT_THAT(m_flag.isSet(), Eq(true));
}
```

#### Mock callback function

Up to this point we have a reliable test that validates that a callback is triggered.  We've
accomplished this by rolling our own _stub_ test double for the callback that we inject into
the unit under test.  When we want to begin testing that the callback is triggered _with the
correct data_, then a stub is insufficient.  We require a spy.  While rolling our own spy is
possible, we can leverage GMock to do it easier and keep our own code more focused.

```c++
TEST_F(StateMachineEvents, NotificationProvidesCorrectState)
{
    NiceMock<MockFunction<void(StateMachine::State)>> listener;
    EXPECT_CALL(listener, Call(StateMachine::State::Busy)).WillOnce(InvokeWithoutArgs([this] { m_flag.set(); }));

    m_stateMachine.subscribe([&listener](StateMachine::State newState) { listener.Call(newState); });
    m_stateMachine.changeState(StateMachine::State::Busy);

    m_flag.wait();
}
```

`MockFunction` defines a class with a single `MOCK_METHODn` method named _Call_ without forcing
us to spell out the entire `class { … };` construct.  This _Call_ method gives us the full GMock
power that we've seen previously with expectations and matchers.  With the _Spy_ capability we
avoid setting our synchronization flag unless the parameter is exactly as we expect.  Should the
unit under test issue a notification to the listener with the wrong parameter, then the
`Notification` test should pass but `NotificationProviesCorrectState` would fail.

The second line of the test has a bit of boilerplate to trigger a function on a specific object.
We could re-define that method on _SyncFlag_ and save us a bit of boilerplate in tests:

```c++
    function<void()> set = [this] {
        {
            std::lock_guard<std::mutex> _(m_mutex);
            m_flag = true;
        }
        m_cv.notify_all();
    };
```

We've changed the `set` method on SyncFlag to be a public member variable of type std::function
that captures _this_.  Callers such as the _Notification_ test continue to function with no
change (_invoke the std::function stored in variable set of the object m_flag and pass it these
(none) parameters_).  But now we have direct access to a std::function that we can pass around
without needing to create our own wrapper each time.

```c++
EXPECT_CALL(listener, Call(StateMachine::State::Busy)).WillOnce(InvokeWithoutArgs(m_flag.set));
```

We don't have control over the definition of `MockFunction::Call`, so it's still up to us to
wrap `Call` when we need to pass it as a `std::function`.

With the power of GMock in our callback we can quickly and easily do further validation such
as sequencing.  The unit under test is expected to notify listeners in the correct order. An
out-of-order notification could leave listeners with the wrong idea of the state.

```c++
TEST_F(StateMachineEvents, NotificationsInOrder)
{
    NiceMock<MockFunction<void(StateMachine::State)>> listener;

    {
        InSequence s;
        EXPECT_CALL(listener, Call(StateMachine::State::Busy));
        EXPECT_CALL(listener, Call(StateMachine::State::Curious));
        EXPECT_CALL(listener, Call(StateMachine::State::Hungry));
        EXPECT_CALL(listener, Call(StateMachine::State::Napping)).WillOnce(InvokeWithoutArgs(m_flag.set));
    }

    m_stateMachine.subscribe([&listener](StateMachine::State newState) { listener.Call(newState); });
    m_stateMachine.changeState(StateMachine::State::Busy);
    m_stateMachine.changeState(StateMachine::State::Curious);
    m_stateMachine.changeState(StateMachine::State::Hungry);
    m_stateMachine.changeState(StateMachine::State::Napping);

    m_flag.wait();
}
```

The `InSequence` object creates a basic restriction on the order of calls to functions.  More
sophisticated ordering restrictions must use the more verbose `InSequence` _statement_ on each
`EXPECT_CALL`.  The `InSequence` _object_ is scope-based, so we have it go out of scope in order
to "finish" our sequence expectation.

Should the events come in an unexpected order GMock will present a failure:

```
Unexpected mock function call - returning directly.
    Function call: Call(4-byte object <03-00 00-00>)
Google Mock tried the following 4 expectations, but none matched:

../../statemachine/src/test/test_statemachine.cpp:81: tried expectation #0: EXPECT_CALL(listener, Call(StateMachine::State::Busy))...
  Expected arg #0: is equal to 4-byte object <02-00 00-00>
           Actual: 4-byte object <03-00 00-00>
         Expected: to be called once
           Actual: never called - unsatisfied and active
../../statemachine/src/test/test_statemachine.cpp:82: tried expectation #1: EXPECT_CALL(listener, Call(StateMachine::State::Curious))...
  Expected arg #0: is equal to 4-byte object <01-00 00-00>
           Actual: 4-byte object <03-00 00-00>
         Expected: to be called once
           Actual: never called - unsatisfied and active
../../statemachine/src/test/test_statemachine.cpp:83: tried expectation #2: EXPECT_CALL(listener, Call(StateMachine::State::Hungry))...
  Expected arg #0: is equal to 4-byte object <00-00 00-00>
           Actual: 4-byte object <03-00 00-00>
         Expected: to be called once
           Actual: never called - unsatisfied and active
../../statemachine/src/test/test_statemachine.cpp:84: tried expectation #3: EXPECT_CALL(listener, Call(StateMachine::State::Napping))...
         Expected: all pre-requisites are satisfied
           Actual: the following immediate pre-requisites are not satisfied:
../../statemachine/src/test/test_statemachine.cpp:83: pre-requisite #0
                   (end of pre-requisites)
         Expected: to be called once
           Actual: never called - unsatisfied and active
```

Note that this call did not match any of the first three expectations because _arg #0 has value
03_ and not the expected value of either 0, 1, or 2.  The fourth expectation failed to match
because it requires that _all pre-requisites are satisfied_ however _pre-requisite #0 (line 83)_
has not been satisfied.  That means we saw _State::Napping_ before we saw _State::Hungry_.

As a bit of cleanup we can move the MockFunction to the test fixture and create our wrapper there
while we're at it.  A little less boilerplate in the existing and future tests.

Further cleanup could be done if we update the `Notification` test to use the _m_listener_ that
is now in the test fixture.  By setting an expectation on _m_listener_ we no longer need to
validate the flag value (which was acting as a basic spy).  At which point _every_ test finishes
by waiting for the flag to be set to know when to validate what calls have been made.  So our
test fixture can handle that for everybody.

With those changes in place we have 3 tests that focus on their own business:

```c++
TEST_F(StateMachineEvents, Notification)
{
    EXPECT_CALL(m_listener, Call(_)).WillOnce(InvokeWithoutArgs(m_flag.set));
    
    m_stateMachine.subscribe(m_listenerFn);
    m_stateMachine.changeState(StateMachine::State::Busy);
}

TEST_F(StateMachineEvents, NotificationProvidesCorrectState)
{
    EXPECT_CALL(m_listener, Call(StateMachine::State::Busy)).WillOnce(InvokeWithoutArgs(m_flag.set));

    m_stateMachine.subscribe(m_listenerFn);
    m_stateMachine.changeState(StateMachine::State::Busy);
}

TEST_F(StateMachineEvents, NotificationsInOrder)
{
    {
        InSequence s;
        EXPECT_CALL(m_listener, Call(StateMachine::State::Busy));
        EXPECT_CALL(m_listener, Call(StateMachine::State::Curious));
        EXPECT_CALL(m_listener, Call(StateMachine::State::Hungry));
        EXPECT_CALL(m_listener, Call(StateMachine::State::Napping)).WillOnce(InvokeWithoutArgs(m_flag.set));
    }

    m_stateMachine.subscribe(m_listenerFn);
    m_stateMachine.changeState(StateMachine::State::Busy);
    m_stateMachine.changeState(StateMachine::State::Curious);
    m_stateMachine.changeState(StateMachine::State::Hungry);
    m_stateMachine.changeState(StateMachine::State::Napping);
}
```

And they run to completion in as short a time as possible:

```
[ RUN      ] StateMachineEvents.Notification
[       OK ] StateMachineEvents.Notification (1 ms)
[ RUN      ] StateMachineEvents.NotificationProvidesCorrectState
[       OK ] StateMachineEvents.NotificationProvidesCorrectState (0 ms)
[ RUN      ] StateMachineEvents.NotificationsInOrder
[       OK ] StateMachineEvents.NotificationsInOrder (0 ms)
```

While still remaining reliable in the face of a slow environment.

Mission accomplished!


Asynchronous calls to non-injected dependencies
-----------------------------------------------

As we saw in [Chapter 2](chapter2.md) the most straightforward way to control the test environment
is when the unit under test accepts its dependencies via injection and the test can provide anything
it wishes.  We now have experience controlling an asynchronous test environment where we can inject
our own object that controls the synchronization within the test.  The technique seen above can be
used even with non-injected dependencies such as those that have test doubles substituted via a link
seam as we saw in [Chapter 3](chapter3.md).

Invoke
------

In previous chapters we've used `Return` to specify the return value of specific invocations of a
given function.  `Return` will take a copy of the value we provide it, then hand it out when required.
In order to cause side effects such as setting our synchronizaton flag we need to have code execute
when the function is invoked.  For that we use `Invoke`.

`Invoke` takes a function and when required it will call the function by passing it the parameters
of the mocked method.  It will then return the value of the invoked function as the return value of
the mocked method.  The signatures must match.

A common situation is to trigger a side-effect without regard to the parameters.  For example
`m_flag.set`.  GMock provides us `InvokeWithoutArgs` to save us from writing wrapper functions
that satisfy the signature and then toss away the arguments.  The return value will still be passed
through to the mocked method.

Testing for non-events
----------------------

A test for `StateMachine` to verify that no event is sent when the StateMachine is set to the same
state that it already is might be written like this:

```c++
TEST_F(StateMachineEvents, NoDuplicateNotifications) {
    EXPECT_CALL(m_listener, Call(StateMachine::State::Hungry)).WillOnce(InvokeWithoutArgs(m_flag.set));

    m_stateMachine.subscribe(m_listenerFn);
    m_stateMachine.changeState(StateMachine::State::Hungry);
    m_stateMachine.changeState(StateMachine::State::Hungry);
}
```

The problem with the above code is that as soon as we see the _first_ event, we begin tearing down
the test.  If we tear down the test too quickly, then we believe no second event came.  But that
does not guarantee that there would not have been a second event if we stuck around to listen.  We
must not be too anxious to stop listening or we'll miss it when it is there.

A slightly tweaked version of the `NoDuplicateNotifications` test would be to stick around and wait
longer to see if a second event comes through.

```c++
TEST_F(StateMachineEvents, NoDuplicateNotifications) {
    EXPECT_CALL(m_listener, Call(StateMachine::State::Hungry)).WillOnce(InvokeWithoutArgs(m_flag.set));

    m_stateMachine.subscribe(m_listenerFn);
    m_stateMachine.changeState(StateMachine::State::Hungry);
    m_stateMachine.changeState(StateMachine::State::Hungry);
    this_thread::sleep_for(chrono::seconds(10));
}
```

An arbitrary sleep for _x_ amoutn of time, then verify that we haven't seen anything has a real problem:
* If _x_ is too short, the test may fail to detect a real problem.
* If _x_ is too long, then it slows everybody down waiting for a test of _nothing_.  Soon the test
  may be disabled entirely.

The trick is to know when to _stop waiting_.

#### Leveraging serialization of events

When events are serialized, then we can stop waiting for a given event when the _next_ event
occurs.  This allows us to use affirmative behaviour to control the test.

```c++

TEST_F(StateMachineEvents, NoDuplicateNotifications) {
    {
        InSequence s;
        EXPECT_CALL(m_listener, Call(StateMachine::State::Hungry));
        EXPECT_CALL(m_listener, Call(StateMachine::State::Curious)).WillOnce(InvokeWithoutArgs(m_flag.set));
    }

    m_stateMachine.subscribe(m_listenerFn);
    m_stateMachine.changeState(StateMachine::State::Hungry);
    m_stateMachine.changeState(StateMachine::State::Hungry);
    m_stateMachine.changeState(StateMachine::State::Curious);
}
```

#### Unserialized async events

Ideas welcome.  Remember that a poor test is worse than no test at all.

Prompt termination
------------------

With a budget of 10ms per test necessary to achieve a scale of thousands of tests, prompt termination
is not a good suggestions, it's a requirement.  If a worker thread polls 10x per second to see whether
it should exit, then that creates a delay of 100ms in each test just waiting for the object to clean
itself up.  With even just a couple dozen of tests on that object it incurs a 2.4s penalty to running
the tests.  And each similar object adds to the shutdown delay of the product causing sluggish reponse.

#### C++11

C++11 primitives allow us to terminate promptly without incurring the expense of polling ever more
frequently.  `StateMachine::monitorState()` demonstrates the use of `std::condition_variable` paired
with an infinite wait.  This thread does not continously wake up if there's nothing to do, but will
react immediately when there _is_ something to do or if it's time to die.

```c++
void StateMachine::monitorState() {
    while (true) {
        vector<State> stateChanges;

        {
            unique_lock<mutex> lock(m_stateMutex);
            m_stateCv.wait(lock, [this] { return !m_stateChanges.empty() || m_terminating; });
            if (m_terminating) {
                return;
            }
            swap(stateChanges, m_stateChanges);
        }

        lock_guard<mutex> _(m_watchersMutex);
        for (const auto& state : stateChanges) {
            for (const auto& callback : m_watchers) {
                callback(state);
            }
        }
    }
}
```

#### Self-pipe

Using a `std::condition_variable` is all well and good when we're waiting on events within C++, but
sometimes a thread is waiting on an event from the system.  The same issue is present if we repeatedly
wake up to check whether we should die: too frequent and we put undue load on the system, too infrequent
and shutdown speeds in both tests and product suffer as a result.

The same concept can be applied using other primitives.  When using `select` or `poll` on a POSIX system
we can use a `pipe` as a means of causing the blocking call to return.  This technique is called _self-pipe_.

```c++
void Mailbox::watchForEvents()
{
    array<pollfd, 2> fds;
    fds[0].fd = m_fd;
    fds[0].events = POLLIN;
    fds[0].revents = 0;
    fds[1].fd = m_controlPipe[0];
    fds[1].events = POLLRDHUP;
    fds[1].revents = 0;

    while (true) {
        constexpr int NoTimeout = -1;
        poll(fds.data(), fds.size(), NoTimeout);

        if (fds[1].revents & POLLHUP) {
            close(fds[1].fd);
            return;
        }

        uint8_t byte;
        auto rc = read(fds[0].fd, &byte, 1);
        m_callback(byte);
    }
}
```

#### Other libraries

With other systems or libraries the types and functions will change but the idea remains the same.
There will be the event or data that we're interested in.  In the C++11 `StateMachine` example this
was the contents of the `m_stateChanges` vector, in the POSIX `Mailbox` example this was data available
via a file descriptor.  There will also be a corresponding function (or family of functions) that
provide a means to wait for the event to occur.  In C++11 this is `std::condition_variable` with a
predicate of our choosing.  In POSIX this is `select` and `poll`.  In Windows thi is `WaitForSingleObject`
and friends.  Other libraries provide their own functions.

In each case we look for an event type that the waiting function is able to respond to and that gives
us control to create the event.  When using a `condition_variable` we set a flag and then poked the
`condition_variable` to have it re-evaluate its predicate (which tests the flag).  When using `select`
or `poll` we create a `pipe` that we keep to ourselves and have `select`/`poll` watch the read end while
we poke the write end at our discretion.  The above example closes the write end.

General recommendations
-----------------------

* Use synchronization tools to control the asynchronous events
    - Never have a blind `sleep`
* If a test executes for longer than 10ms (Release build on Linux), improve it until it's <10ms
* Unit tests are white-box testing. Use the knowledge of the implementation to your advantage
    - If events are flushed on termination, the tests don't need to perform as much synchronization
    - If events are serialized, detecting the absence of an event is possible
* Write/fix product code to be event driven
    - If product forces an arbitrary sleep, it's impossible to have unit tests execute in less time

When dealing with multithreading, increase your estimate.  It requires much more time to do right.
