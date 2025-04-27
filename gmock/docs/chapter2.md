Chapter 2 - Mocking Dependencies
================================

Key Concepts
------------

* Test doubles (dummy, stub, spy/mock, fake)
* Default actions
* Verifying behaviour
* Controlling return values
* Build system organization
* General recommendations

Test Doubles
------------

Isolating a piece (or "unit") of code that has dependencies on other code may require
substituting the dependencies.  This code replacement is termed "test doubles".  Where
a stunt double replaces an actor within the scope of a stunt, a test double replaces
product code within the scope of a test.

Not all code needs to be substituted.  A lot of basic functionality like std::vector or
std::mutex would *not* be substituted.  Code that is not yet written, is "heavy", or
that has complex behaviour that we wish to control a prime candidates to replace in
unit tests.

Some literature gives names to test doubles based on their level of sophistication,
while others call everything a "mock" (because it's quicker to say and can be used as
a verb).  We'll explore them individually.

#### Dummy

The most basic substitution is when we need to pass *some* object, but that object is
never actually used.  In this case the test double does not need to do anything sane and
is called a Dummy.  Implementations of functions are free to `assert(false);` or similar.

To implement a dummy by hand to satisfy an Authenticator interface it may look like this:

```c++
class DummyAuthenticator : public Authenticator
{
public:
    bool authenticate(const std::string& username, const std::string& password) const override
    {
        assert(false);  // Die an obvious death
    }
};
```

When using GMock, dummies can be created with roughly the same amount of effort (after
learning GMock's syntax).  An equivalent DummyAuthenticator using GMock would look like this:

```c++
class DummyAuthenticator : public Authenticator
{
public:
    MOCK_CONST_METHOD2(authenticate, bool(const std::string&, const std::string&));
};
```

Methods are defined with either `MOCK_METHODn` or `MOCK_CONST_METHODn` depending whether or
not the method is `const`.  The `n` is the number of parameters the method takes.  If the
number doesn't align with the number of arguments provided, you'll get a scary compile error.

The arguments to `MOCK_(CONST_)METHODn` are first the name of the function followed by the
return value and parameter types.  The syntax is similar to defining a `std::function`.

Dummy objects are easy to define but have limited value.  If the unit under test required
one to be available, then presumably *some* code path would eventually want to *use* it.
Given that we want to test as much functionality as we can, then a hand-rolled dummy will
become insufficient.  The GMock-style of dummy can be extended to satisfy our needs.  In
short, use GMock even for dummy objects.

#### Stub

Stubs are functions with fixed results without doing real work.  They are essentially
dummies that *do* get called and return something that doesn't blow up the system.  In
the example of an authentication module it would be common to return "thumbs-up" for
any authentication request, allowing the unit tests to run on any system regardless of
credentials on the system.

Implementing a stub by hand is essentially writing a dummy and choosing a sane return value:

```c++
class StubAuthenticator : public Authenticator
{
public:
    bool authenticate(const std::string& username, const std::string& password) const override
    {
        return true;  // Everyone welcome!
    }
};
```

With GMock we don't have direct access to the function definition.  Instead we specify the
desired return value in the class' constructor:

```c++
// stubauthenticator.h
class StubAuthenticator : public Authenticator
{
public:
    StubAuthenticator();
    
    MOCK_CONST_METHOD2(authenticate, bool(const std::string&, const std::string&));
};

// stubauthenticator.cpp
using namespace testing;

StubAuthenticator::StubAuthenticator()
{
    ON_CALL(*this, authenticate(_, _)).WillByDefault(Return(true));
}
```

The first portion (`ON_CALL(this, authenticate(_, _))`) specifies what we're referring to.
In this case, the authenticate method on `this`.  The special notation of `_` (more precisely
`testing::_`) is a wildcard matcher.  Anything goes.  When all arguments are `_` such as in
this example we obtain the same behaviour as the hand-rolled implementation (ie: any and all
calls to the function).  

The second portion (`WillByDefault(Return(true))`) specifies the return value in something
resembling English with a bit more typing than the `return true;` of the hand-rolled variant.

If we do not tell GMock what we want the return value to be, then it will return `0` for
numeric return types, `false` for booleans, `nullptr` for pointer types, and nothing for `void`.
If these values are the desired behaviour, then there is no need to write the `ON_CALL` line.

Stubs extend the usefulness of Dummy objects by allowing functions to be called.  For functions
that have no return value a Stub may be all that is required for tests.  But, as with Dummy
objects, Stubs are not a complete solution for all situations.  In particular when there is a return
value, then the calling code presumably takes different actions depending on the result. Having
a fixed result prevents execution of the alternative logic flows.

When there is no return value, the GMock code seen in DummyAuthenticator provides a Stub for
the same effort as writing the stub by hand.  When there *is* a return value, typically we
will require greater flexibility than a single-purpose stub, and thus writing the Stub using
GMock is well worth the extra couple lines of typing.

#### Spy/Mock

A test double that provides information regarding functions that are called such as how many
times it was called or what the arguments were is called a Spy.  Assertions that verify
function calls made possible by Spies are prone to create fragile tests if not done with
great care.  If a test is written that asserts that a function is called *n* times and later
the algorithm is updated to call the function *n-1* times, then the test will fail even
though the behaviour may still be correct.

When the validation of the spied function calls is rolled in to the test double itself, the
double is called a Mock.  Both the DummyAuthenticator and StubAuthenticator written above
already spy on the method invocations and will validate behaviour when they go out of scope.
Tests may immediately define their expectations on the callers behaviour.

A test written to verify that the Authenticator *is* consulted when we attempt to login a
user would look like this:

```c++
TEST(Session, CredentialsChecked)
{
    MockAuthenticator auth;
    UserSession sess(auth);
    
    EXPECT_CALL(auth, authenticate(_, _));
    
    sess.signIn("bob", "secret");
}
```

Note that `EXPECT_CALL` is an anticipation of a future event.  The expectation must be
declared before causing the action to occur.  It will be verified when the mock object
goes out of scope.

When `EXPECT_CALL` is used without specifying how many calls to expect, then GMock will
treat it as *exactly one call*.  If the unit under test fails to invoke `authenticate`
on the provided authenticator, the test will fail:

```
[ RUN      ] Session.CredentialsChecked
../../session/src/test/test_session.cpp:16: Failure
Actual function call count doesn't match EXPECT_CALL(auth, authenticate(_, _))...
         Expected: to be called once
           Actual: never called - unsatisfied and active
[  FAILED  ] Session.CredentialsChecked (1 ms)
```

If it calls `authenticate` multiple times, the test will also fail:

```
[ RUN      ] Session.CredentialsChecked
../../session/src/test/test_session.cpp:16: Failure
Mock function called more times than expected - taking default action specified at:
../../authenticator/mock/mockauthenticator.cpp:7:
    Function call: authenticate(@0x7fffe330afe0 "bob", @0x7fffe330b000 "secret")
          Returns: true
         Expected: to be called once
           Actual: called twice - over-saturated and active
[  FAILED  ] Session.CredentialsChecked (0 ms)
```

In situations where the correct behaviour is a fixed number of invocations, then we
*want* the test to fail should it be invoked an incorect number of times.  This may be
for correctness or performance reasons when some functions are particularly expensive.

Use caution when spying on behaviour to avoid creating fragile tests that will make your
future self cry.  Consider a companion function on the Authenticator that verifies that
a username is legal.  We could write a test that ensures it is invoked and not neglected.
We might write it like this:

```c++
TEST(Session, UsernameChecked)
{
    MockAuthenticator auth;
    UserSession sess(auth);
    
    EXPECT_CALL(auth, usernameIsWellFormed(_));
    
    sess.signIn("bob", "secret");
}
```

This test would pass and without further attention could find its way to master.  A few
months later when the session logic is being extended or cleaned up, it may make sense to
check the username twice (for whatever reason -- play along here).  At that point the unit
test would fail and yet the code is still correct.  The username is still being checked.
A fragile unit test such as this discourages code refactoring because of they require
attention instead of quietly providing validation.

In this example the intent behind the test is actually "verify that the username is
checked (at least once)".  This refined description leads to the following test code:

```c++
TEST(Session, UsernameChecked)
{
    MockAuthenticator auth;
    UserSession sess(auth);
    
    EXPECT_CALL(auth, usernameIsWellFormed(_)).Times(AtLeast(1));
    
    sess.signIn("bob", "secret");
}
```

Also of note is that *UsernameChecked* sets an expectation on `usernameIsWellFormed` but
no expectation whatsoever on `authenticate`.  Likewise *CredentialsChecked* sets an
expectation on `authenticate` but turns a blind eye to `usernameIsWellFormed`.  This
minimizes the coupling between the implementation and the test.  This focus improves the
readability and reduces the fragility of the tests.

Both of these examples are checking whether (or how many times) a method is invoked,
but spies provide us additional information which is extremely valuable to these tests.
The tests should fail if the *wrong* credentials are provided to the Authenticator.
The following have tightened expectations:

```c++
TEST(Session, CredentialsChecked)
{
    MockAuthenticator auth;
    UserSession sess(auth);
    
    const string username = "bob";
    const string password = "secret";
    
    EXPECT_CALL(auth, authenticate(StrEq(username), StrEq(password)));
    
    sess.signIn(username, password);
}

TEST(Session, UsernameChecked)
{
    MockAuthenticator auth;
    UserSession sess(auth);
    
    const string username = "bob";
    
    EXPECT_CALL(auth, usernameIsWellFormed(StrEq(username))).Times(AtLeast(1));
    
    sess.signIn(username, "secret");
}
```

This more focused test would fail if the implementation passed the wrong value to
`usernameIsWellFormed`.  Should this happen the failure report would include two
complaints: the expected call never happend, and a call occurred that was not expected:

```
[ RUN      ] Session.UsernameChecked
unknown file: Failure

Unexpected mock function call - taking default action specified at:
../../authenticator/mock/mockauthenticator.cpp:8:
    Function call: usernameIsWellFormed(@0x7ffd2259a020 "secret")
          Returns: true
Google Mock tried the following 1 expectation, but it didn't match:

../../session/src/test/test_session.cpp:28: EXPECT_CALL(auth, usernameIsWellFormed(StrEq(username)))...
  Expected arg #0: is equal to "bob"
           Actual: "secret"
         Expected: to be called at least once
           Actual: never called - unsatisfied and active
../../session/src/test/test_session.cpp:28: Failure
Actual function call count doesn't match EXPECT_CALL(auth, usernameIsWellFormed(StrEq(username)))...
         Expected: to be called at least once
           Actual: never called - unsatisfied and active
[  FAILED  ] Session.UsernameChecked (0 ms)
```

#### Fake

Validating the happy path only gets us so far.  One of the major strengths of unit tests
is the ability to cheaply validate unhappy paths.  And there are many more unhappy paths
than happy paths.  Creating a unique stub to use as a test double each time we need a
different return value does not scale.  Test doubles that can return different values
based on input are called Fakes.  If we were to hand-roll a fake for `authenticate` it
might look something like this:

```c++
class FakeAuthenticator : public Authenticator
{
public:
    bool authenticate(const std::string& username, const std::string& password) const override
    {
        return username != "baduser";  // Use "baduser" to test authentication failure
    }
};
```

This neither scales well nor is very clear when reading through the tests themselves.
Why would `authenticate("baduser", "foo")` return false but `authenticate("wronguser", "foo")`
return true?  (Answer: It's magic!)

The test doubles written with GMock for the earlier types already provide everything
necessary to use the object as a fake:

```c++
TEST(Session, FailedAuthentication)
{
    MockAuthenticator auth;
    UserSession sess(auth);
    
    // For this test we want authentication to fail
    ON_CALL(auth, authenticate(_, _)).WillByDefault(Return(false));
    
    sess.signIn("bob", "secret");
    EXPECT_THAT(sess.isSignedIn(), Eq(false));
}
```

Clean output
------------

The above tests produce very noisy output as they are currently written:

```
[ RUN      ] Session.FailedAuthentication

GMOCK WARNING:
Uninteresting mock function call - taking default action specified at:
../../authenticator/mock/mockauthenticator.cpp:8:
    Function call: usernameIsWellFormed(@0x7ffebb249b40 "bob")
          Returns: true
NOTE: You can safely ignore the above warning unless this call should not happen.  Do not suppress
it by blindly adding an EXPECT_CALL() if you don't mean to enforce the call.  See
https://github.com/google/googletest/blob/master/googlemock/docs/CookBook.md#knowing-when-to-expect
for details.

GMOCK WARNING:
Uninteresting mock function call - taking default action specified at:
../../session/src/test/test_session.cpp:50:
    Function call: authenticate(@0x7ffebb249b40 "bob", @0x7ffebb249b60 "secret")
          Returns: false
NOTE: You can safely ignore the above warning unless this call should not happen.  Do not suppress
it by blindly adding an EXPECT_CALL() if you don't mean to enforce the call.  See
https://github.com/google/googletest/blob/master/googlemock/docs/CookBook.md#knowing-when-to-expect
for details.
[       OK ] Session.FailedAuthentication (0 ms)
```

This extra noise can quickly create a very large haystack where a true error can hide.  The
default behaviour for mock objects in GMock is "Naggy" mocks which warn (nag) when there is
no expectation set for a given method invocation.  Sometimes while developing it may be
useful to have this extra trace information, but the majority of the time this is just noise
that reduces the signal-to-noise ratio.

Wrapping the mock objects in `NiceMock<…>` suppresses the noise and only reports errors.

```
[ RUN      ] Session.FailedAuthentication
[       OK ] Session.FailedAuthentication (0 ms)
```

Heed the warnings from the GMock developers in the warning message itself (above) and in
their documentation:

> Our general recommendation is to use nice mocks (not yet the default) most of the time,
> use naggy mocks (the current default) when developing or debugging tests, and use strict
> mocks only as the last resort.

Build system organization
-------------------------

#### Build time efficiency

The GMock authors draw attention to the fact that despite appearances, the constructor and destructor
of a mock class can become very expensive for the compiler.  If the constructor or destructor is
omitted or defined in the header (including `= default`), then this compilation time will be incurred
each time the header is `#include`'d.  For efficient builds both the constructor and destructor should
always be defined in the corresponding .cpp file.  The headers will then be more lightweight for tests
to reference and the implementations will be made available at link time.

Instead of this:

```c++
class MockAuthenticator : public Authenticator
{
public:
    MockAuthenticator() = default;
    
    MOCK_CONST_METHOD2(authenticate, bool(const std::string&, const std::string&));
};
```

Write this instead:

```c++
// mockauthenticator.h
class MockAuthenticator : public Authenticator
{
public:
    MockAuthenticator();
    ~MockAuthenticator();
    
    MOCK_CONST_METHOD2(authenticate, bool(const std::string&, const std::string&));
};

// mockauthenticator.cpp
MockAuthenticator::MockAuthenticator() = default;
MockAuthenticator::~MockAuthenticator() = default;
```

Note that the destructor is *not* marked `override`.  This is because we cannot specify
`override` for the mock methods (which may or may not be overriding virtual methods),
and some compilers will astutely warn (or error) when a class makes use of `override` but
contains another method that *does* override without declaring its intention to override.
In short, classes that use GMock generally forgo the use of `override`.

#### Sharing test doubles

Writing a test double inline with your test works well enough for today's you, but your future
you or your coworker will often want the same dependency replaced when testing another module.
Even when a module is consumed by only one other module today, tomorrow there may be a second
module that wishes to also consume it.  Wouldn't it be nice if the mock were trivally available
without resorting to copy/paste?

Given a module's directory structure:

```
authenticator/
+- api/
+- src/
|  +- test/
+- mock/
```

Where:
* `api/` holds the public header files that define the API of the module.
* `src/` holds the implementation of the module.
* `src/test/` holds the unit tests for the implementation.
* `mock/` holds the mock implementation (test double) that conforms to `api/`.

Note that in this example `test/` is a subdirectory of `src/` as it is specific to the
implementation found in `src/`.  In a future chapter when we cover Abstract Tests we'll see
a `test/` directory as a sibling to `api/`.

The standard CMake code that builds the authenticator library would look like this:

```cmake
add_library( authenticator STATIC
  api/authenticator.h
  src/authenticator.cpp
)
target_include_directories( authenticator
  PUBLIC
    api
)
```

To create a library holding the authenticator's test double that can be easily referenced
by code that wishes to substitute the authenticator we want:
* Preserve the `api/` directory as a public include directory as that contains the public API.
* Provide the `mock/` directory as an additional public include directory to provide control of the mock.
* Provide GMock as a dependency.  Public as the mock's header file will require GMock's headers.

The macro `TeraMock` handles these details.  A CMakeLists.txt file in the `mock/` directory would
contain the following:

```cmake
TeraMock( MODULE authenticator
  SOURCES
    mockauthenticator.h
    mockauthenticator.cpp
)
```

Where `MODULE foo` references the library we are mocking.  The name must match what was
given to `add_library( foo …)`.  Note that TeraMock will create a target named `mock_foo` so
only one mock may exist in the build tree for a given library.  It will become obvious pretty
quickly if a mock has been created (using TeraMock) for a library that lives somewhere else
in the build tree.

The `SOURCES …` lists all the source files to compile into this library.  As with other libraries
the header files are not built directly but are included in order to populate IDEs that do not
show the directory structure such as VisualStudio.  The real implementation for mocks live in
the GMock library and as such there is no need to create additional directories.

#### Linking to a mock

Given library *session* that links to library *authenticator*, the unit test wants to
sever the link to *authenticator* and replace it with *mock_authenticator*.  The `TeraTest`
macro seen in [Chapter 1](chapter1.md) severs the linkage for us.  We need only specify
the module we wish inserted in its place.

```cmake
TeraTest( UNIT session
  FRAMEWORK GMock
  TESTS
    test_session.cpp
  MOCK
    authenticator
)
```

`MOCK …` accepts a list of targets.  For each item in the list it will link to `mock_<name>`.
Since the mock is expected to be a drop-in replacement for the real deal, the unit under
test should not even be aware of this substitution and the tests can leverage the spy/fake
abilities of the test double.

General recommendations
-----------------------

* GMock is the one-stop-shop for your test double needs.
* Expectations in tests should accurately reflect the desired behaviour.
* Use great care when leveraging Spy/Mock functionality.  Avoid coupling as much as possible.
* Place the mock's c'tor and d'tor in the .cpp file.
* Have the mock define default (happy path) behaviour.  Consumers can then focus on the exceptions.
