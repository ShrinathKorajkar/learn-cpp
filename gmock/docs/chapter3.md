Chapter 3 - Replacing non-virtual functions
===========================================

Key Concepts
------------

* Test fixtures
* Link seams
* Delegating to a mock/fake

Simple Test Fixtures
--------------------

In prior chapters we've seen tests begin to grow to contain some boilerplate.  For example:

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

The above test from Chapter 2 contains the special situation for the test (authenticate
returning false), the action to trigger the behaviour being tested, and the validation
of the result we're interested in.  But it also contains boilerplate that does not
contribute to the test itself nor does it improve understanding the purpose or behaviour
of the test.  In short, 2 out of 5 lines of the test is noise.

To make matters worse, this noise is often repeated in multiple tests.  As the units
under test gain further dependencies, testing requires even more boilerplate in order
to create a controlled environment for the unit under test to execute.

Test fixtures provide a way to abstract away the boilerplate so that the tests themselves
remain focused on testing without getting sidetracked with boilerplate.

A test fixture, in its simplest form, is merely a class that derives from `::testing::Test`.
Tests that use the fixture are classes that derive from the fixture class.  Data can be
accessed directly provided the fixture declares it as either `public` or `protected`.

```c++
using namespace testing;

class SessionAuthentication : public Test
{
public:
    SessionAuthentication()
      : m_sess(m_auth)
    {}
    
protected:
    MockAuthenticator m_auth;
    UserSession m_sess;
};
```

Following the rules of class inheritance in C++, the fixture's constructor will be
run to completion before our test runs.  Similarly the destructor will be run
after our test and clean up any member variables held by the fixture.

To have a test use a given fixture, it must be defined with `TEST_F` instead of
`TEST` that we've seen earlier.  This distinction is due to limitations of the C++
macro system preventing one macro from handling both cases.  The first argument
(the test case name) must be the name of the fixture.

With _SessionAuthentication_ in place, the following two tests behave the same:

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

TEST_F(SessionAuthentication, FailedAuthentication)
{
    // For this test we want authentication to fail
    ON_CALL(m_auth, authenticate(_, _)).WillByDefault(Return(false));
    
    m_sess.signIn("bob", "secret");
    EXPECT_THAT(m_sess.isSignedIn(), Eq(false));
}
```

With a test fixture in place, new tests can skip the boilerplate and focus on the interesting
stuff.

Note that you cannot use the same test case name for the fixture and non-fixture tests.
It does compile, but GTest errors out at runtime.  Fortunately the message is pretty helpful:

```
[ RUN      ] Session.FailedAuthentication
C:\Users\afuller\CMakeBuilds\7ed0afa1-209d-9c34-ac3c-f15e3d291063\build\x86-Debug\deps\GoogleTest\1.8.0\googletest\src/gtest.cc(2301): error: Failed
All tests in the same test case must use the same test fixture
class, so mixing TEST_F and TEST in the same test case is
illegal.  In test case Session,
test FailedAuthentication is defined using TEST_F but
test CredentialsChecked is defined using TEST.  You probably
want to change the TEST to TEST_F or move it to another test
case.
[  FAILED  ] Session.FailedAuthentication (0 ms)
```

On the other hand if `TEST_F` references a non-existent fixture, the compile will fail
with an error about an undefined base class.  This message is clear only if we remember
that `TEST_F` is creating a class behind the scenes that inherits from the fixture.

There are more to fixtures, but this suffices for our current needs.

Substitution Points
-------------------

Unit tests require a controlled environment.

Code that has no dependencies other than the function arguments provided has its environment
controlled entirely by the arguments passed in by the test.  We saw an example of this in
[Chapter 1](chapter1.md).  The point where we are able to influence the environment for the
test is at the function call itself.

Code that has a virtual interface provided for its use has its environment controlled by
leveraging function overriding.  We saw an example of this in [Chapter 2](chapter2.md).
The point where we are able to influence the environment for the test is at runtime as
the vtable is consulted at each function call.

These substitution points are convenient as they occur very _late_.  Code remains unchanged
from production and minimal effort is required in order to establish a controlled environment
in which to perform the tests.  Their drawback is where they can be used.  The first example
only works for code with no dependencies.  ie: the leaf nodes of a dependency graph.  As
software becomes more complex, the leaf nodes represent a much smaller proportion of the whole.
The second example only works for code that makes exclusive use of virtual functions.  Not
all code uses virtual functions either for performance reasons, technical (C code does not
support virtual functions), or design (certain functions should not be overridden in product).

How do we create a controlled environment for code that calls non-virtual functions?

There are other substitution points that give us access to establish a controlled test
environment.  Chapters 1 and 2 showed exampled of the late end of the spectrum (the call site
and vtable lookup stage).  At the early extreme of the spectrum sits the preprocessor stage
before even the compile begins.  The early end of the spectrum is the most generic -- it can
work for anything, but it is also the least maintainable.  Anyone who has had to maintain code
filled with `#ifdef`'s can attest to the extra complexity it creates.

Link seams
----------

The _link_ stage provides a substitution point (dubbed _Link Seam_) that lies on the later
end of the spectrum, but not as extreme as the _runtime_ stage we've already seen.

Without virtual functions, the decision of which code to execute for a given function
call is determined at link time.  This "link seam" provides us the next latest point where
we can replace code with a test double.

#### How it works

Header files provide function signatures to potential callers so that the compiler can
determine whether a particular function call is valid.  But the implementation typically
resides in a library.  After compilation the linker will combine the calling library
with the library containing the callee's implementation and the final binary will be
as it should.

If we have two libraries that both provide implementations for the same function signatures
(say _A_ and _A'_), then we can have the linker combine _B+A_ for product and _B+A'_ for
tests.  The _B_ library is unchanged allowing us to test the real production code, but the _A'_
contents grant us control over the _B_'s dependencies.

#### Where can it be used

The caller and callee must live in different libraries as the linker combines (links)
libraries together but does not divide libraries.

Substituting a class with non-virtual functions
-----------------------------------------------

Given a class with non-virtual functions such as the following:

```c++
using Pixel = uint32_t;
class PixelStuff
{
public:
    PixelStuff();
    ~PixelStuff();
    
    void addPixels( const std::vector<Pixel>& pixels );
    std::string quickHash( const std::vector<Pixel>& pixels );
    std::string expensiveHash( const std::vector<Pixel>& pixels );
    
private:
    std::vector<Pixel>& m_pixels;
}
```

we can create a test double by providing an alternate implementation that we bring in to the
unit test executable via a link seam while product links in the real implementation.

```c++
PixelStuff::PixelStuff() = default;
PixelStuff::~PixelStuff() = default;

void PixelStuff::addPixels const std::vector<Pixel>& pixels )
{
}

std::string PixelStuff::quickHash( const std::vector<Pixel>& pixels )
{
    return "deadbeef";
}

std::string PixelStuff::expensiveHash( const std::vector<Pixel>& pixels )
{
    return "c00lcafe";
}
```

This is straightforward if all we need is a _dummy_ or _stub_.  Write-only interfaces such as a
logging interface often don't need anything more than a stub and the above code is sufficient.
If we require a mock or a fake, then we need to have access to control the test double to either
set expectations (mock) or control the return value (fake).  The above class definition does not
provide any access to our test double.  To achieve mock or fake capabilities we can use an approach
that we'll see later when we discuss substituting free functions.

Substituting a PImpl class
--------------------------

When a class uses the PImpl (Pointer to Implementation) pattern we gain greater control of the
implementation.  If in addition to the PImpl pattern the class also provides a constructor that
accepts the implementation, then we gain a very convenient access point to control our
implementation permitting a full mock or fake test double.

```c++
using Pixel = uint32_t;
class PixelStuffImpl;
class PixelStuff
{
public:
    PixelStuff();
    PixelStuff(std::unique_ptr<PixelStuffImpl> impl);
    ~PixelStuff();
    
    void addPixels( const std::vector<Pixel>& pixels );
    std::string quickHash( const std::vector<Pixel>& pixels ) const;
    std::string expensiveHash( const std::vector<Pixel>& pixels ) const;
    
private:
    std::unique_ptr<PixelStuffImpl> m_impl;
};
```

Consumers see only the above class definition which hides the details of the _Impl_ class.  This
pattern is common for maintaining binary compatibility while permitting the implementation to evolve.
Our test double provides its own `PixelStuffImpl` class definition and exposes it so that tests can
first create the implementation (to have access to it for mocking or faking purposes) before passing
it to the wrapping class.  When the unit under test accesses the class that has been so constructed,
all the calls are then delegated to the test double.  Effectively this is a double-hop of dependency
injection to get around the lack of virtual functions.

```c++
class PixelStuffImpl
{
public:
    PixelStuffImpl();
    virtual ~PixelStuffImpl();
    
    MOCK_METHOD1( addPixels, void(const std::vector<Pixel>&) );
    MOCK_CONST_METHOD1( quickHash, std::string(const std::vector<Pixel>&));
    MOCK_CONST_METHOD1( expensiveHash, std::string(const std::vector<Pixel>&));
};
```

The test double library must also contain an implementation for the wrapper class.

```c++
PixelStuff::PixelStuff( std::unique_ptr<PixelStuffImpl> impl )
  : m_impl( move(impl) )
{}
PixelStuff::~PixelStuff() = default;
    
void PixelStuff::addPixels( const std::vector<Pixel>& pixels )
{
    m_impl->addPixels(pixels);
}
std::string PixelStuff::quickHash( const std::vector<Pixel>& pixels ) const
{
    return m_impl->quickHash(pixels);
}
std::string PixelStuff::expensiveHash( const std::vector<Pixel>& pixels ) const
{
    return m_impl->expensiveHash(pixels);
}

PixelStuffImpl::PixelStuffImpl() = default;
PixelStuffImpl::~PixelStuffImpl() = default;
```

Unit tests then have direct access to the test double.

```c++
using namespace testing;
class PixelCorrectness : public Test
{
public:
    PixelCorrectness()
      : m_pixelWorker([this]{
            unique_ptr<PixelStuffImpl> impl(new PixelStuffImpl());
            m_pixelStuffImpl = impl.get();
            return unique_ptr<PixelStuff>(new PixelStuff(move(impl)));
        }())
    {}

protected:
    PixelStuffImpl* m_pixelStuffImpl;
    PixelWorker m_pixelWorker;
};

TEST_F(PixelCorrectness, QuickHashCollission)
{
    const vector<Pixel> pixelsA{ 123, 123, 123 };
    const vector<Pixel> pixelsB{ 2, 2 };
    
    ON_CALL(*m_pixelStuffImpl, quickHash(_)).WillByDefault(Return("f00"));
    ON_CALL(*m_pixelStuffImpl, expensiveHash(ElementsAreArray(pixelsA))).WillByDefault(Return("aa"));
    ON_CALL(*m_pixelStuffImpl, expensiveHash(ElementsAreArray(pixelsB))).WillByDefault(Return("bb"));
    
    m_pixelWorker.addPixels(pixelsA);
    m_pixelWorker.addPixels(pixelsB);
    EXPECT_THAT(m_pixelWorker.numUniqueBlobs(), Eq(2));
}

TEST_F(PixelCorrectness, DuplicatePixels)
{
    const vector<Pixel> pixels{ 123, 123, 123 };

    ON_CALL(*m_pixelStuffImpl, quickHash(_)).WillByDefault(Return("f00"));
    ON_CALL(*m_pixelStuffImpl, expensiveHash(_)).WillByDefault(Return("aa"));
    
    m_pixelWorker.addPixels(pixels);
    m_pixelWorker.addPixels(pixels);
    EXPECT_THAT(m_pixelWorker.numUniqueBlobs(), Eq(1));
}
```

Substituting free functions
---------------------------

That's all well and good when you have an object that conveniently enables dependency injection.
How do we create a controlled environment when the code being tested calls free functions?

#### Substituting the implementation

Replacing the production implementation with a double for testing is no different than what we
saw above when implementing an alternate `PixelStuff`.  The production implementation resides
in a library that the linker includes to form the final production binary while the test double
resides in a different library that the linker includes when creating the test binaries.

```c++
// logger.h
void logMessage( const std::string& msg );

// logger.cpp
void logMessage( const std::string& msg )
{
    // Here by fancy logging work
}

// mocklogger.cpp
void logMessage( const std::string& msg )
{
    // Do nothing.  Nobody will see it anyway.
}
```

#### Delegating to a mock/fake

Even for write-only interfaces, there may come a time when we want to leverage a _spy_ to validate
that an event was fired.  Perhaps an external tool parses log files and it would be an error to
issue a new version of the product where the log message was removed or even rephrased.  Functions
that return values require the power of a _fake_ as soon as we deviate from the happy path.  That
means right away when writing unit tests.

But free functions have no class.  No state.  GMock gives us the full power of _mocks_ and _fakes_,
but wrapped up in a class and must hold state.

Fortunately the statelessness of free functions means that we don't need to differentiate between
invocations of the functions since that's impossible in product anyway.  If the test double's
implementation were to delegate to a mock instance accessible to the test, then we get everything
we wish for:

* Production code remains unmodified
* Calls to dependencies are sent to a controlled environment
* The environment is fully under the control of the test to create any scenario it desires

To achieve all this, we first create a class that mimics the free functions:

```c++
class MockLogger
{
public:
    MockLogger();
    ~MockLogger();
    
    MOCK_CONST_METHOD1(logMessage, void(const std::string&));
};
```

The test double's definition then delegates to the mock logger.  But wait! How does the stateless
function know where the instance of the `MockLogger` lives?  We don't want to couple the test
double to individual tests even at the best of times.  Even more so when we are likely to have
multiple consumers who each should remain independent.  Fortunately we've already established that
we don't need to differentiate between function invocations.  So using a single mock is perfectly
acceptable.

Be careful not to create a global `MockLogger` and expose it via some additional API
such as a _Singleton_ class because the mock's validation is done within its destructor.  The
mock _must_ be destroyed inside each and every test case.  Instead we'll have the `MockLogger`
coordinate with the test double implementation, but leave the object lifetime up to the individual
tests:

```c++
namespace {
MockLogger* g_mockLogger = nullptr; // Raw pointer - this does not own the object
} // end anonymous namespace

MockLogger::MockLogger()
{
    if( g_mockLogger ) {
        throw runtime_error("Cannot have more than one MockLogger at the same time.");
    }
    g_mockLogger = this;
}
MockLogger::~MockLogger()
{
    g_mockLogger = nullptr;
}

void logMessage( const std::string& msg )
{
    if( g_mockLogger ) {
        g_mockLogger->logMessage(msg); // Full mock/fake powers
    }
    // else the best we can get is a stub.  Good enough for happy path if the test
    // didn't care to create a MockLogger.
}
```

```c++
class SessionAuthentication : public Test
{
protected:
    NiceMock<MockLogger> m_logger;
    NiceMock<MockAuthenticator> m_auth;
    UserSession m_sess;
};

TEST_F(SessionAuthentication, FailedAuthLogMessage)
{
    // LogParser from ACME, Inc. watches for this string in the logs
    EXPECT_CALL(m_logger, logMessage(HasSubstr("Failed to authenticate")));
    
    ON_CALL(m_auth, authenticate(_, _)).WillByDefault(Return(false));
    m_sess.signIn("bob", "secret");
}
```

Delegating class functions to a mock/fake
-----------------------------------------

Non-virtual functions that we saw in the non-PImpl class can delegate to a mock/fake in the same
way that we did for the free functions.  All instances of the class would delegate to the same
instance of the mock, but the could define its method signature to accept the `this` pointer
from the callees to distinguish between the callee instances if desired.

General recommendations
-----------------------

* Use test fixtures to remove boilerplate from individual tests
* There is no one-size-fits-all method for test double substitution
* Avoid polluting production APIs with test-only APIs
    - The purist would reject even the PImpl class that added a constructor that accepts an
      externally constructed Impl instance as it is not used in production
* Late substitutions are typically preferred for their maintainability, but are restricted
  in where they can be used

In short, use your best judgement.
