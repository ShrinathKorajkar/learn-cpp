Chapter 7 - Death Tests
=======================

Key Concepts
------------

* Testing exceptions
* Verifying exit codes
* Verifying messages
* Death test naming
* Death test gotchas

Testing The Unhappy Paths
-------------------------

Previous chapters have covered ways of providing different environments and inputs to a
piece of code under test.  But all the examples have assumed that the code under test would
do something inteligible and not fall over.

Some code when confronted with certain conditions _will_ fall over.  Either somewhat
gracefully by throwing an exception that may or may not be caught higher up, or by forcing
the entire process to terminate unconditionally.  GTest provides tools for us to test even
these unhappy paths.

Testing Exceptions
------------------

### The Naïve Approach

Without being aware that GTest provides a dedicated check for exceptions we could roll
our own test and have it look something like this:

```c++
TEST(ExceptionTest, OutOfRangeGeneric)
{
    try {
        getItem(42);
    } catch(const exception&) {
        // What we expected
        return;
    }
    FAIL() << "No exception was thrown";
}
```
If we wanted to be more precise in our validation, we might want to verify that a _specific_
exception is thrown (or a derived class of it):

```c++
TEST(ExceptionTest, OutOfRangeSpecific)
{
    try {
        getItem(42);
    } catch(const out_of_range&) {
        // What we expected
        return;
    } catch(const exception& e) {
        FAIL() << "Unexpected exception: " << e.what();
    }
    FAIL() << "No exception was thrown";
}
```

The verbosity of the above solutions hinders the readability of the tests.

### Using GTest

GTest provides `EXPECT_*` and `ASSERT_*` checks for exceptions.  The distinction of `EXPECT_*` vs. `ASSERT_*` is the same as we've seen previously where both will record a failure, but `EXPECT_*` will continue execution while `ASSERT_*` will exit the current
function.

`*_ANY_THROW` will verify that _some_ kind of exception was thrown.  Our first example can
be re-written as this:

```c++
TEST(ExceptionTest, OutOfRangeGeneric)
{
    EXPECT_ANY_THROW(getItem(42));
}
```

Aside from less typing, it also makes it immediately clear to the reader what is being tested
(since it is no longer buried within 7 lines and an extra level of indentation), as well as
what is expected (`ANY_THROW`).

```
[ RUN      ] ExceptionTest.OutOfRangeGeneric
/home/local/TERADICI/afuller/src/gmock-tutorial/repo/reaper/src/test/test_reaper.cpp:43: Failure
Expected: getItem(42) throws an exception.
  Actual: it doesn't.
[  FAILED  ] ExceptionTest.OutOfRangeGeneric (0 ms)
```

The Second example can be re-written using `*_THROW`:

```c++
TEST(ExceptionTest, OutOfRangeSpecific)
{
    EXPECT_THROW(getItem(42), out_of_range);
}
```

Again, clarity is improved by removing 8 lines of boilerplate and keeping one salient line.
The second argument to `EXPECT_THROW` is the type of exception expected to be thrown.
If an exception is thrown of a derived type, it will pass, but a non-derived type will fail
the check.

```
[ RUN      ] ExceptionTest.OutOfRangeSpecific
/home/local/TERADICI/afuller/src/gmock-tutorial/repo/reaper/src/test/test_reaper.cpp:48: Failure
Expected: getItem(42) throws an exception of type out_of_range.
  Actual: it throws a different type.
[  FAILED  ] ExceptionTest.OutOfRangeSpecific (1 ms)
```

GTest also provides `*_NO_THROW`.  In practice this is rarely useful as GTest will inherently
fail a test if an exception rises out of the test function.  It can be useful if you find a
need to have a try/catch within the test and you want to ensure particular calls are _not_
the ones who raised the exception.  In this scenario take a moment to re-evaluate whether
the test needs to be that complex.

```c++
TEST(ExceptionTest, UncaughtException)
{
    throw runtime_error("GTest will fail this test due to an uncaught exception");
}
```

```
[ RUN      ] ExceptionTest.UncaughtException
unknown file: Failure
C++ exception with description "GTest will fail this test due to an uncaught exception" thrown in the test body.
[  FAILED  ] ExceptionTest.UncaughtException (0 ms)
```

### Augmenting GTest's Check

Taking it a step further we can validate that the exception description contains useful
information.  GTest doesn't provide a pre-made solution, but we can craft our own:

```c++
TEST(ExceptionTest, MessageCheck)
{
    EXPECT_THROW(
    {
        try {
            getItem(42);
        } catch(const out_of_range& e) {
            EXPECT_THAT(e.what(), HasSubstr("important words"));
            throw;
        }
    },
    out_of_range);
}
```

The `EXPECT_THROW` still handles diagnosing when no exception is thrown, or the wrong type
of exception is thrown.  We augment the body to further check the message of the exception
when the correct type is thrown.

This approach still has boilerplate that is not interesting for the test.  When we want this
behaviour even once or twice we can clean it up with a little macro:

```c++
#define EXPECT_THROW_MSG(body, exception_type, msg_matcher) \
    EXPECT_THROW(                                           \
    {                                                       \
        try {                                               \
            body;                                           \
        } catch(const exception_type& e) {                  \
            EXPECT_THAT(e.what(), msg_matcher);             \
            throw;                                          \
        }                                                   \
    },                                                      \
    exception_type);
```

The test then becomes:

```c++
TEST(ExceptionTest, MessageCheck)
{
    EXPECT_THROW_MSG(getItem(42), out_of_range, HasSubstr("important words"));
}
```

This now has all the checks that `EXPECT_THROW` handles with an extra, controllable, check
of the exception's message.

```
[ RUN      ] ExceptionTest.MessageCheck
/home/local/TERADICI/afuller/src/gmock-tutorial/repo/reaper/src/test/test_reaper.cpp:86: Failure
Value of: e.what()
Expected: has substring "important words"
  Actual: 0x5560c86b6258 pointing to "Index 42 is out of range. Some important wordz." (of type char const*)
[  FAILED  ] ExceptionTest.MessageCheck (0 ms)
```

Death Tests
-----------

Testing a codepath that results in process termination is a whole different beast than
checking the return value of a function, or testing for a thrown exception.  The difficulty
with process termination is that the program is now _dead_ and there was nothing we could
do about it.

GTest has done the heavy lifting and turns this situation from scary-and-impossible-to-test
to testable-with-some-caution.

### Testing For Death

As with the other verification functions in GTest, the death test checks come in `ASSERT_*`
and `EXPECT_*` pairs with the same semantics we've already seen.

To test a code path that terminates (perhaps due to a failed assertion), use the `*_DEATH`
pair of checks.

```c++
TEST(ExampleDeathTest, Nullptr)
{
    EXPECT_DEATH(doStuff(nullptr), "");
}
```

If `doStuff` does _not_ terminate the program, then the test fails.  If it _does_ terminate the program, then the test succeeds and yet the test and subsequent tests continue to run.

```
[ RUN      ] ExampleDeathTest.Nullptr
/home/local/TERADICI/afuller/src/gmock-tutorial/repo/reaper/src/test/test_reaper.cpp:93: Failure
Death test: doStuff(nullptr)
    Result: failed to die.
 Error msg:
[  DEATH   ] 
[  FAILED  ] ExampleDeathTest.Nullptr (3 ms)
```

### Testing Exit Codes

Let's consider a situation where specific exit codes have been documented to indicate
particular failures.  In our tests we want to ensure that the _correct_ exit code is emitted
when the program terminates for a particular reason.  The `*_EXIT` pair of checks let us
match on the exit code.

```c++
TEST(ExampleDeathTest, ExitCode4WhenBadCommand)
{
    EXPECT_EXIT(parseCommand("bogus"), ExitedWithCode(4), "");
}
```

The second argument is a function or functor that takes an integer and returns a boolean.
If it returns `false` then the `*_EXIT` check will fail.  In practice the `ExitedWithCode`
helper provided by GTest is likely all that is needed.  GTest also provides `KilledBySignal`
which is not available on Windows.

```
[ RUN      ] ExampleDeathTest.ExitCode4WhenBadCommand
/home/local/TERADICI/afuller/src/gmock-tutorial/repo/reaper/src/test/test_reaper.cpp:97: Failure
Death test: parseCommand("bogus")
    Result: died but not with expected exit code:
            Exited with exit status 5
Actual msg:
[  DEATH   ] Line one
[  DEATH   ] Time to die
[  DEATH   ] last line
[  DEATH   ] 
[  FAILED  ] ExampleDeathTest.ExitCode4WhenBadCommand (1 ms)
```

### Testing Normal Termination

A normal termination (exit code 0) can only be checked with `*_EXIT` as `*_DEATH` verifies
not only that the program terminated, but also that it exited with a non-zero exit code.

```c++
TEST(ExampleDeathTest, NormalExit)
{
    EXPECT_EXIT(stop(), ExitedWithCode(0), "");
}
```

### Verifying Stderr

The last argument of both `*_EXIT` and `*_DEATH` take a regex that will test `stderr`.  A
normal termination (exit code 0) is unlikely to write to stderr, but for abnormal termination
stderr commonly provides a message to the user and it can be validated here.

```c++
TEST(ExampleDeathTest, Nullptr)
{
    EXPECT_DEATH(doStuff(nullptr), "input .* null");
}
```

If the regex does not match, then the check fails.  An empty regex `""` matches anything
including an empty stderr.

```
[ RUN      ] ExampleDeathTest.Nullptr
/home/local/TERADICI/afuller/src/gmock-tutorial/repo/reaper/src/test/test_reaper.cpp:92: Failure
Death test: doStuff(nullptr)
    Result: died but not with expected error.
  Expected: input .* null
Actual msg:
[  DEATH   ] something generic may or may not have once been null. Blowing up.
[  DEATH   ] 
[  FAILED  ] ExampleDeathTest.Nullptr (215 ms)
```

### The Magic Behind The Curtain

Behind the scenes, `*_DEATH` and `*_EXIT` spawn another process and have this extra process
execute the code being checked while the original process sits back and watches, then
evaluates the exit code and checks stderr against the regex before finally moving on to
the next order of business.

This spawning of a separate process has two key implications:

* Anything that happens within the child process stays in the child process, including:
  * freeing of resources
  * satisfying `EXPECT_CALL` invocations
* Spawning another process doesn't always play well when the original process has threads
  * best to avoid having any threads spawned until _after_ the extra process is spawned
  * the child process may freely use threads

#### GMock Calls And Death Tests

Being aware of what's going on behind the scenes to make death tests possible lets us
understand why the following test reports an unsatisfied mock call:

```c++
TEST(ExampleDeathTest, FunctionCalledExpectationOutside)
{
    MockFunction<void()> mockFn;
    EXPECT_CALL(mockFn, Call());

    EXPECT_DEATH({
        mockFn.Call();
        abort();
    }, "");
}
```

```
[ RUN      ] ExampleDeathTest.FunctionCalledExpectationOutside
/home/local/TERADICI/afuller/src/gmock-tutorial/repo/reaper/src/test/test_reaper.cpp:108: Failure
Actual function call count doesn't match EXPECT_CALL(mockFn, Call())...
         Expected: to be called once
           Actual: never called - unsatisfied and active
[  FAILED  ] ExampleDeathTest.FunctionCalledExpectationOutside (185 ms)
```

With the entire implementation inline we can clearly see that `mockFn::Call` _is_ called.
Knowing that the secondary process is the one to evaluate the body of `EXPECT_DEATH` while
the main process does not, we understand that from the main process' perspective, the test
looks similar to this:

```c++
TEST(ExampleDeathTest, FunctionCalled)
{
    MockFunction<void()> mockFn;
    EXPECT_CALL(mockFn, Call());
    
    // Nothing more executed
}
```

The solution is to place the `EXPECT_CALL` _inside_ the death test's body such that the
process that is expected to call it has the expectation set while the other process does
not:

```c++
TEST(ExampleDeathTest, FunctionCalledExpectationInside)
{
    MockFunction<void()> mockFn;
    
    EXPECT_DEATH({
        EXPECT_CALL(mockFn, Call());
        mockFn.Call();
        abort();
    }, "");
}
```

```
[ RUN      ] ExampleDeathTest.FunctionCalledExpectationInside
[       OK ] ExampleDeathTest.FunctionCalledExpectationInside (160 ms)
```

If the dying process fails to meet the expectation, that failure is _not_ detected by the
main process.  The main process had no expectation of its own and only watches the spawned process for the exit status.  The following test does _not_ fail despite the unfulfilled `EXPECT_CALL`:

```c++
TEST(ExampleDeathTest, FunctionCalled)
{
    MockFunction<void()> mockFn;
    
    EXPECT_DEATH({
        EXPECT_CALL(mockFn, Call());
        // mockFn.Call();
        abort();
    }, "");
}
```

Despite not validating whether expectations are met inside the death test, they may still be
useful to control the behaviour of the unit under test in order to trigger the desired code
path.

### Threads In Death Tests

The GTest authors stress repeatedly to avoid spawning any threads in death tests as spawning
the necessary subprocess isn't always reliable in the presence of threads.  GTest will emit a
warning if threads are detected, but won't fail the test outright.  The success of the test
depends on whether the spawn succeeds or not.  To be safe, avoid threads in death tests.

```c++
TEST(ExampleDeathTest, Thread)
{
    auto worker = async(launch::async, getNumber);

    EXPECT_DEATH({
        exit(42);
    }, "");

    auto answer = worker.get();
}
```

```
[WARNING] deps/GoogleTest/1.8.0/googletest/src/gtest-death-test.cc:836:: Death tests use fork(), which is unsafe particularly in a threaded context. For this test, Google Test detected 2 threads.
```

### Naming Death Tests

There is a little-known detail that can wreck havoc in death thests: there is an extra "manager"
thread that is spawned the moment the first thread is created.  This manager thread sticks around
till the end of the process.  That means that a given process can never return to a no-threads
state once it has crossed the multithreaded line even once.  Since death tests should only be
run in a single-threaded process and since spawning threads is perfectly acceptable for non-death
tests, the order that tests execute is very important.

GTest handles this all for us as long as we follow their established guideline that all death
tests (and only death tests) suffix their test suite with `DeathTest` (singlar, CamelCase).
When GTest sees this naming convention, it will execute those test suites before any others.

To use a test fixture for both death and non-death tests, create an alias for the fixture:

```c++
class SomeFixture : public Test ...
TEST_F(SomeFixture, LivingStuff) ...

using SomeFixtureDeathTest = SomeFixture;
TEST_F(SomeFixtureDeathTest, DeadlyStuff) ...
```

General Recommendations
-----------------------

* Leverage GTest to test exceptional and deadly code paths
* Name death tests with `DeathTest` (singular) as the test suite suffix
* Avoid spawning any threads in DeathTests
* Be cognizant that the body of death tests are executed in a separate process
