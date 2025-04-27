Chapter 1 - My First Test
=========================

Key Concepts
------------

* GTest vs. GMock
* Creating a test
* Assertions and expectations
* General recommendations

GTest vs. GMock
---------------

Google Test (GTest) v1.0 was released in 2008 and provides a framework to write tests.
GTest is based on the xUnit architecture and thus has a similar overall structure as
JUnit and CppUnit (among many others).

Google Mock (GMock) v1.0 was released later in 2008 and provides functionality to
incorporate [mock objects](https://en.wikipedia.org/wiki/Mock_object) in tests.
GMock may be used within any test framework and is not bound to GTest.

In practice GMock is typically used in combination with GTest and in 2015 the two
projects combined into one (GTest).  The source tree and header files continue to
reflect the GTest / GMock distinction.

Creating a test
---------------

A test comprises 3 parts:

1. The code being tested
2. The behaviour being asserted
3. GTest / GMock to handle the behind-the-scenes work

In a codebase using CMake and leveraging Teradici's CMake helpers (ie: `TeraInit()` is
called in the top level CMakeLists.txt) GTest with GMock is automatically available and
the function `TeraTest` makes defining a test target very concise.

#### TeraTest

Given a static library named `blob-parser` containing free functions we can begin writing
unit tests with the following bit of CMake code:

```cmake
TeraTest( UNIT blob-parser
  FRAMEWORK GMock
  TESTS
    test_blobparser.cpp
)
```

*TeraTest* is a convenience function to create an executable that links to both
GTest/GMock and also the library under test (the argument to *UNIT*).  The source
files provided as the arguments to *TESTS* are compiled into the executable and the
result is registered with CMake as a unit test to be triggered when `make check` or
`ctest` are run.  Pass/fail information is also provided in a way that TeamCity
understands.

#### Tests

The behaviour to assert is placed in the source file(s) of the test:

```c++
#include <blobparser.h>
#include <gmock/gmock.h>

TEST(BlobParserBasics, Invalid)
{
    // TODO: Write me!
}
```

Access to GTest is provided in *gtest/gtest.h* and GMock is provided in *gmock/gmock.h*.
GMock leverages GTest and publicly brings it along for the ride and can be viewed as a
superset of the two libraries, in practice *gmock/gmock.h* alone serves to "bring in the
test framework".

Individual tests are defined using the *TEST* macro which takes two arguments: the first
is a test case name and the second is the name of the individual test.  Tests within a
given test case are grouped together when viewing the test results.

#### Rules for naming tests

* *Do not* use `_` in either argument to the *TEST* macro.  GTest generates a class named
  first_second_Test.  Having an underscore in either part could result in generating a
  class with an illegal (such as having two consecutive underscores) or duplicate name
  (such as `TEST( Foo_Test, Bar )` and `TEST( Foo, Test_Bar )`).  Use camel case instead
  and avoid the problem altogether.
* Avoid including the word "test" in either the test case name or the test name.  It's
  redundant.

Assertions and expectations
---------------------------

After the half dozen lines of boilerplate are in place we can begin writing tests.  Tests
consist of triggering controlled behaviour and then validating the behaviour.

#### GTest checks

###### Basic checks

The simplest check is asserting *true* or *false*:

```c++
TEST(BlobParserBasics, Invalid)
{
    ASSERT_FALSE(isValid({}));
}
```

Should this validation fail the error message will contain additional information to
aide in diagnosing the problem:

```
[ RUN      ] BlobParserBasics.Invalid
../../blobparser/src/test/test_blobparser.cpp:6: Failure
Value of: isValid({})
  Actual: true
Expected: false
[  FAILED  ] BlobParserBasics.Invalid (0 ms)
```

Checks come in two flavours: *assertions* and *expectations*.  Both types will fail the
test if the condition is not met and provide the same error message.  The distinction
is that expectations will continue execution even after a failed check while assertions
will stop.  More precisely assertions will exit the current function.  Use the `ASSERT_`
variation of checks when it does not make sense to continue processing (eg: when checking
that a pointer is non-null prior to dereferencing it).  Use the `EXPECT_` variation of
checks when further checks would provide additional help in understanding the nature of
the failure (eg: when validating both the size and contents of a collection returned, if
the size doesn't match, knowing which elements were missing or added).

##### Binary comparisons

GTest can also check for equality (EQ), inequality (NE), less than (LT), etc.
Prior to February 2016 the equality printed the error report assuming that the first
argument was the expected value and the second argument was the value being tested.
Now both parameters are treated the same way so order doesn't matter.

```c++
TEST(BlobParserBasics, CountElements)
{
    EXPECT_EQ(numElements({}), 0);
    EXPECT_EQ(0, numElements({}));
}
```

The following error is printed on failure:

```
[ RUN      ] BlobParserBasics.CountElements
../../blobparser/src/test/test_blobparser.cpp:11: Failure
      Expected: numElements({})
      Which is: 42
To be equal to: 0
../../blobparser/src/test/test_blobparser.cpp:12: Failure
      Expected: 0
To be equal to: numElements({})
      Which is: 42
[  FAILED  ] BlobParserBasics.CountElements (0 ms)
```

The additional context provided is very valuable.  Always prefer `ASSERT_EQ(a, b)`
over `ASSERT_TRUE(a == b)`

##### String comparisons

GTest provides checks for strings, but C-strings and std::strings are handled differently.
`*_EQ` since it uses the `==` operator will compare std::strings for equivalence,
but C-strings will only have their addresses compared.  To handle string equivalence of
C-strings, GTest provides `*_STREQ` (counterpart to `*_EQ`), `*_STRNE`
(counterpart to `*_NE`), as well as `*_STRCASEEQ` and `*_STRCASENE` which do case-insensitive
comparisons which have no counterpart for std::strings.

The inconsistencies in handling std::strings vs. string literals or other C-strings is
awkward and renders tests less focused if the author must convert string types in order
to perform checks.  Fortunately GMock improves the situation.

#### GMock checks

GMock takes a different approach to validation.  It maintains the same `ASSERT_` vs.
`EXPECT_` pairing with the same behaviour, but it adds the concept of *matchers* to
replace the need for a dedicated macro for every type of check.  Matchers are declared
in the *testing* namespace.  Test code is much more readable by leveraging `using namespace testing`.

GMock provides the `ASSERT_THAT(…)` and `EXPECT_THAT(…)` macros that accept matchers
as their second argument.  Some of the basic matchers provide the same functionality as
GMock's dedicated macros.

##### Basic checks

Checking for truth using a matcher is done by passing *true* or *false* to either the *Eq*
or *Ne* matcher.

```c++
TEST(BlobParserBasics, Invalid)
{
    EXPECT_FALSE(isValid({}));
    EXPECT_THAT(isValid({}), Eq(false));
}
```

In the event of a failure, both would provide useful diagnostics:

```
[ RUN      ] BlobParserBasics.Invalid
../../blobparser/src/test/test_blobparser.cpp:8: Failure
Value of: isValid({})
  Actual: true
Expected: false
../../blobparser/src/test/test_blobparser.cpp:9: Failure
Value of: isValid({})
Expected: is equal to false
  Actual: true (of type bool)
[  FAILED  ] BlobParserBasics.Invalid (0 ms)
```

##### Binary comparisons

Using GMock's matchers binary comparisons perform the same task and provide equivalent
diagnostics compared to GTest's macros.  GMock's matchers enforce argument ordering
(the matcher is always the second argument) and have the side effect of reading a little
closer to English than GTest's macros.  GTest's macros read more similar to normal Polish
notation.

```c++
TEST(BlobParserBasics, ElementThreshold)
{
    EXPECT_LT(numElements({}), 10);
    EXPECT_THAT(numElements({}), Lt(10));
}
```

Both forms generate useful diagnostics:

```
[ RUN      ] BlobParserBasics.ElementThreshold
../../blobparser/src/test/test_blobparser.cpp:21: Failure
Expected: (numElements({})) < (10), actual: 42 vs 10
../../blobparser/src/test/test_blobparser.cpp:22: Failure
Value of: numElements({})
Expected: is < 10
  Actual: 42 (of type unsigned long)
[  FAILED  ] BlobParserBasics.ElementThreshold (0 ms)
```

##### String comparisons

GMock provides matchers for string equality that accept both C-strings as well as
std::strings so a C-string can be compared to a std::string.

While the *Eq* and *Ne* matchers can compare std::strings due to their *==*
operator, and GMock will even handle a `char*` as a string in the matcher when it
sees that it is comparing to a *std::string*, but if both sides are `char*` then
the pointed address will be compared instead.  Always use *StrEq* or *StrNe* when
verifying string equivalence.

```c++
TEST( BlobParserBasics, Vendor )
{
    EXPECT_THAT(getVendor({0x0a}), Eq("Teradici"));
    EXPECT_THAT(getVendor({0x0a}).c_str(), Eq("Teradici"));
    EXPECT_THAT(getVendor({0x0a}), StrEq("Teradici"));
    EXPECT_THAT(getVendor({0x0a}).c_str(), StrEq("Teradici"));
}
```

The second expectation fails because pointers are being compared instead of
the string values.

```
[ RUN      ] BlobParserBasics.Vendor
../../blobparser/src/test/test_blobparser.cpp:28: Failure
Value of: getVendor({0x0a}).c_str()
Expected: is equal to 0x4cd01d pointing to "Teradici"
  Actual: 0x7ffc7580da50 pointing to "Teradici" (of type char const*)
[  FAILED  ] BlobParserBasics.Vendor (0 ms)
```

GMock also provides `StrCaseEq` and `StrCaseNe` as improved versions of GTest's
case-insensitive macros due to their ability to accept C-strings and std::strings.

Further string comparisons are possible with other string matchers in GMock:
*StartsWith*, *EndsWith*, *HasSubstr*, *MatchesRegex* and *ContainsRegex*.  Note that
regexes in GTest (what GMock delegates to) uses the POSIX extended regex syntax (not
PCRE) on POSIX systems (Cygwin/Linux/Mac) but on Windows it uses its own implementation
that is much more limited.  For tests that must also run on Windows, regex support
is much more basic.

##### Matchers vs. GTest macros

GMock's matchers render many of GTest's macros redundant and are much more powerful
for comparisons as we'll cover in later chapters.  But some macros provided by
GTest are more involved than simple comparisons and continue to provide value not
available in GMock.  These include exception tests and death tests.

General recommendations
-----------------------

* #include <gmock/gmock.h> as the only GTest/GMock related include file.
* Choose `EXPECT_` vs. `ASSERT_` as appropriate.
* Choose the form that provides the most useful error message in the event of failure.
  (eg: choose `ASSERT_THAT( a, Eq(b) )` over `ASSERT_TRUE( a == b )`)
* Prefer `ASSERT_THAT` and `EXPECT_THAT` to leverage the power of matchers.  Consistency
  with other checks is a bonus.
* Leverage `using namespace testing;` to improve readability of tests.