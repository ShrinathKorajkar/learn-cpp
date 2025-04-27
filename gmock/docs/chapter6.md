Chapter 6 - Parameterized Tests
===============================

Key Concepts
------------

* Value-parameterized tests
* Pretty names
* Abstract tests
* Typed tests

Reusing the same test with different inputs
-------------------------------------------

Often a given test requires a specific input, but occasionally we want to execute the
exact same test with a variety of inputs.  Consider a `trim` function intended to remove
leading and trailing whitespace.  A single test might look like this:

```c++
TEST(Trim, Whitespace)
{
    EXPECT_THAT(stringutils::trim(" trimmed "), StrEq("trimmed"));
}
```

Adding more tests that vary only on the input would duplicate the boilerplate:

```c++
TEST(Trim, LeadingSpaces)
{
    EXPECT_THAT(stringutils::trim("  trimmed"), StrEq("trimmed"));
}
TEST(Trim, TrailingSpaces)
{
    EXPECT_THAT(stringutils::trim("trimmed   "), StrEq("trimmed"));
}
TEST(Trim, Tabs)
{
    EXPECT_THAT(stringutils::trim("\ttrimmed\t"), StrEq("trimmed"));
}
TEST(Trim, MixedTabsAndSpaces)
{
    EXPECT_THAT(stringutils::trim("\ttrimmed  "), StrEq("trimmed"));
}
```

The duplicated boilerplate obscures what the interesting parts of the test are.  This
is amplified as the test becomes more elaborate such as having multiple lines of
EXPECT_CALLs, or post-assertions.

Another approach would be to have a single test that checks all the input variations:

```c++
TEST(Trim, Whitespace)
{
    EXPECT_THAT(stringutils::trim(" trimmed "), StrEq("trimmed"));
    EXPECT_THAT(stringutils::trim("  trimmed"), StrEq("trimmed"));
    EXPECT_THAT(stringutils::trim("trimmed   "), StrEq("trimmed"));
    EXPECT_THAT(stringutils::trim("\ttrimmed\t"), StrEq("trimmed"));
    EXPECT_THAT(stringutils::trim("\ttrimmed  "), StrEq("trimmed"));
}
```

This approach has the advantage of reducing duplication, but the disadvantage of losing
the ability to see when one (or some) of the inputs fail while others pass.  If any one
fails, then the test as a whole is marked as failed.

Value Parameterized Tests
-------------------------

An alternate approach is what GTest calls Parameterized Tests.  It requires a fixed
amount of boilerplate up front, but then scales well with added test inputs.  It will
create a test for each input so that it's easy to distinguish between one/some/all inputs
failing.

### Test Fixture

The first thing that's required is to use a test fixture that derives from both `Test`
and also `WithParamInterface<T>`.  GTest provides a base class `TestWithParam<T>` to do
exactly that.  All of those base classes are in the `::testing` namespace.

The template argument is the type of the input for the tests.  For our `trim` example
we'll use a `std::string`.

The value itself is available via `GetParam()`.  For readability in tests, this is
often wrapped in a function that provides a more tailored name and potentially any
massaging of the value as we'll see later in this chapter.

```c++
class TrimTest : public TestWithParam<string>
{
public:
    const string& value() const
    {
        return GetParam();
    }
};

```

### Test Case

With a parameterized fixture available we can write the test case to use it.  Previously
we've seen `TEST_F` for test cases that utilize test fixtures.  When using a parameterized
fixture we must use the `TEST_P` macro instead.

```c++
TEST_P(TrimTest, Whitespace)
{
    ASSERT_THAT(stringutils::trim(value()), StrEq("trimmed"));
}
```

### Test Values

Now that we have a test that accepts injected values, we need to provides those values.
GTest refers to this part as instantiating the test case.  Similar to creating multiple
instances of a class each with a different value, we create multiple instances of a test
each with a different value.

```c++
INSTANTIATE_TEST_CASE_P(
  Trim, TrimTest,
  Values(
    "  trimmed     ", "trimmed", "trimmed ", " trimmed", "\ntrimmed", "trimmed\n", "\ttrimmed", "trimmed\t",
    "\rtrimmed", "trimmed\r", "\r\t\n trimmed \r\t\n", "\r\rtrimmed\n\n"));
```

We need to provide 3 parameters to `INSTANTIATE_TEST_CASE_P`.

* The first argument is a prefix for each of the tests and must be unique if instantiating
  the test multiple times. Here we're only instantiating once, so it's automatically unique.
  Later int his chapter we'll see an example where we would instantiate multiple times and the
  name must be more carefully chosen.
* The second argument is the name of the test _fixture_ (not the individual test case)
* The third argument is the set of inputs.  For raw (hardcoded) values use `Values` (also
  in the `::testing` namespace) to wrap them together.  Alternatives to `Values` are `Range`
  `ValuesIn`, `Bool` and `Combine`.  We will only be using `Values` in this chapter.

### Output

The above code will produce the following output when run (provided the implementation
is bug-free):

```
[----------] 12 tests from Trim/TrimTest
[ RUN      ] Trim/TrimTest.Whitespace/0
[       OK ] Trim/TrimTest.Whitespace/0 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/1
[       OK ] Trim/TrimTest.Whitespace/1 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/2
[       OK ] Trim/TrimTest.Whitespace/2 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/3
[       OK ] Trim/TrimTest.Whitespace/3 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/4
[       OK ] Trim/TrimTest.Whitespace/4 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/5
[       OK ] Trim/TrimTest.Whitespace/5 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/6
[       OK ] Trim/TrimTest.Whitespace/6 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/7
[       OK ] Trim/TrimTest.Whitespace/7 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/8
[       OK ] Trim/TrimTest.Whitespace/8 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/9
[       OK ] Trim/TrimTest.Whitespace/9 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/10
[       OK ] Trim/TrimTest.Whitespace/10 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/11
[       OK ] Trim/TrimTest.Whitespace/11 (0 ms)
[----------] 12 tests from Trim/TrimTest (0 ms total)
```

This produced 12 tests (one for each of the 12 values we provided to `INSTANTIATE_TEST_CASE_P`).
Each test is prefixed with `Trim` which is what we provided as the first argument when
instantiating the test.  The centre section is what we would normally see if we had used `TEST`
or `TEST_F` which is a combination of the test fixture's name and the name of the test itself.
Finally at the end is an index of the test values so that the name is unique.

If the unit under test fails for certain inputs, then we'll see this in the output:

```
[----------] 12 tests from Trim/TrimTest
[ RUN      ] Trim/TrimTest.Whitespace/0
[       OK ] Trim/TrimTest.Whitespace/0 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/1
[       OK ] Trim/TrimTest.Whitespace/1 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/2
[       OK ] Trim/TrimTest.Whitespace/2 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/3
[       OK ] Trim/TrimTest.Whitespace/3 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/4
../../stringutils/src/test/test_stringutils.cpp:19: Failure
Value of: stringutils::trim(value())
Expected: is equal to "trimmed"
  Actual: "\ntrimmed"
[  FAILED  ] Trim/TrimTest.Whitespace/4, where GetParam() = "\ntrimmed" (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/5
[       OK ] Trim/TrimTest.Whitespace/5 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/6
[       OK ] Trim/TrimTest.Whitespace/6 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/7
[       OK ] Trim/TrimTest.Whitespace/7 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/8
[       OK ] Trim/TrimTest.Whitespace/8 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/9
[       OK ] Trim/TrimTest.Whitespace/9 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/10
../../stringutils/src/test/test_stringutils.cpp:19: Failure
Value of: stringutils::trim(value())
Expected: is equal to "trimmed"
  Actual: "\n trimmed"
[  FAILED  ] Trim/TrimTest.Whitespace/10, where GetParam() = "\r\t\n trimmed \r\t\n" (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/11
[       OK ] Trim/TrimTest.Whitespace/11 (0 ms)
[----------] 12 tests from Trim/TrimTest (0 ms total)
```

The diagnostic message includes the value of the input.

### Adding new values

Unsurprisingly, adding a new input to test is done by adjusting the list passed to
`INSTANTIATE_TEST_CASE_P`:

```c++
INSTANTIATE_TEST_CASE_P(
  Trim, TrimTest,
  Values(
    "  trimmed     ", "trimmed", "trimmed ", " trimmed", "\ntrimmed", "trimmed\n", "\ttrimmed", "trimmed\t",
    "\rtrimmed", "trimmed\r", "\r\t\n trimmed \r\t\n", "\r\rtrimmed\n\n", "trimmed"));
```

```
[----------] 13 tests from Trim/TrimTest
[ RUN      ] Trim/TrimTest.Whitespace/0
[       OK ] Trim/TrimTest.Whitespace/0 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/1
[       OK ] Trim/TrimTest.Whitespace/1 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/2
[       OK ] Trim/TrimTest.Whitespace/2 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/3
[       OK ] Trim/TrimTest.Whitespace/3 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/4
[       OK ] Trim/TrimTest.Whitespace/4 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/5
[       OK ] Trim/TrimTest.Whitespace/5 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/6
[       OK ] Trim/TrimTest.Whitespace/6 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/7
[       OK ] Trim/TrimTest.Whitespace/7 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/8
[       OK ] Trim/TrimTest.Whitespace/8 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/9
[       OK ] Trim/TrimTest.Whitespace/9 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/10
[       OK ] Trim/TrimTest.Whitespace/10 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/11
[       OK ] Trim/TrimTest.Whitespace/11 (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/12
[       OK ] Trim/TrimTest.Whitespace/12 (0 ms)
[----------] 13 tests from Trim/TrimTest (0 ms total)
```

Composite Values
----------------

A single value can quickly become restrictive.  Fortunately GTest doesn't care what
type the value is.  We are free to use a composite type of our own choosing.  This
is commonly a custom `struct` or simply a `tuple`.

The following test requires 3 inputs and validates against a 4th:

```c++
TEST(ADPCMEncoderQualityTest, calculatesCorrectQuality)
{
    ADPCMEncoder e(chrono::milliseconds(20));
    ASSERT_THAT(e.adjustQuality(10.0, 450, 0), Eq(true));
    ASSERT_THAT(e.getCompressedSize(), Eq(970));
}
```

This test can be parameterized by using a tuple as the parameter type:

```c++
constexpr chrono::milliseconds TwentyMsFrame(20);

class ADPCMEncoderQualityTest : public TestWithParam<tuple<float, uint32_t, float, unsigned>>
{
public:
    float bandwidthActive()
    {
        return get<0>(GetParam());
    }
    uint32_t bandwidthLimit()
    {
        return get<1>(GetParam());
    }
    float queueFillRatio()
    {
        return get<2>(GetParam());
    }
    unsigned expectedCompressedSize()
    {
        return get<3>(GetParam());
    }
};

TEST_P(ADPCMEncoderQualityTest, calculatesCorrectQuality)
{
    ADPCMEncoder e(TwentyMsFrame);
    ASSERT_THAT(e.adjustQuality(bandwidthActive(), bandwidthLimit(), queueFillRatio()), Eq(true));
    ASSERT_THAT(e.getCompressedSize(), Eq(expectedCompressedSize()));
}

INSTANTIATE_TEST_CASE_P(
  ADPCMEncoder, ADPCMEncoderQualityTest,
  Values(
    make_tuple(10.0, 450, 0, 970), make_tuple(10.0, 449, 0, 165), make_tuple(10.0, 90, 0, 165),
    make_tuple(10.0, 89, 0, 85), make_tuple(1.12, 500, 0, 970), make_tuple(1.11, 500, 0, 165),
    make_tuple(0.71, 500, 0, 165), make_tuple(0.69, 500, 0, 85), make_tuple(10.0, 500, 0.6, 85)));
```

Obtaining values from a tuple is not very self-explanatory (what is item #3?).  Wrapper functions
in the test fixture provide names for clarity's sake.

The usual power of fixtures are available, so the above example could just as easily be written
like this:

```c++
class ADPCMEncoderQualityTest : public TestWithParam<tuple<float, uint32_t, float, unsigned>>
{
public:
    ADPCMEncoderQualityTest()
      : m_uut(TwentyMsFrame)
      , m_bandwidthActive(get<0>(GetParam()))
      , m_bandwidthLimit(get<1>(GetParam()))
      , m_queueFillRatio(get<2>(GetParam()))
      , m_expectedCompressedSize(get<3>(GetParam()))
    {
    }

    ADPCMEncoder m_uut;
    const float m_bandwidthActive;
    const uint32_t m_bandwidthLimit;
    const float m_queueFillRatio;
    const unsigned m_expectedCompressedSize;
};

TEST_P(ADPCMEncoderQualityTest, calculatesCorrectQuality)
{
    ASSERT_THAT(m_uut.adjustQuality(m_bandwidthActive, m_bandwidthLimit, m_queueFillRatio), Eq(true));
    ASSERT_THAT(m_uut.getCompressedSize(), Eq(m_expectedCompressedSize));
}
```

They are functionally identical and the output of the test is the same in either case:

```
[----------] 9 tests from ADPCMEncoder/ADPCMEncoderQualityTest
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/0
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/0 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/1
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/1 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/2
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/2 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/3
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/3 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/4
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/4 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/5
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/5 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/6
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/6 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/7
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/7 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/8
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/8 (0 ms)
[----------] 9 tests from ADPCMEncoder/ADPCMEncoderQualityTest (0 ms total)
```

Should a specific test fail, GTest will provide the inputs as best it can:

```
[----------] 9 tests from ADPCMEncoder/ADPCMEncoderQualityTest
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/0
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/0 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/1
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/1 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/2
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/2 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/3
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/3 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/4
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/4 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/5
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/5 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/6
../../audio/src/test/test_audio.cpp:60: Failure
Value of: e.getCompressedSize()
Expected: is equal to 165
  Actual: 0 (of type unsigned long)
[  FAILED  ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/6, where GetParam() = (0.71, 500, 0, 165) (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/7
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/7 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/8
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/8 (0 ms)
[----------] 9 tests from ADPCMEncoder/ADPCMEncoderQualityTest (0 ms total)
```

Nicer Names
-----------

A counter to itemize the tests is functional but neither pretty not clear when viewing the
list of tests.  The diagnostic message helps to identify failed tests.  But with a little
work we can have even the passing tests look better.

`INSTANTIATE_TEST_CASE_P` can optionally take a 4th argument which is a function that
takes a `TestParamInfo<class ParamType>` and returns a `std::string`.  This string
must be non-empty, unique, consist of only ASCII alphanumeric characters and not contain
an underscore.

GTest provides a built-in function `PrintToStringParamName` (also in the `testing`
namespace).  In our ADPCM Encoder example this built-in function is inadequate as
printing the parameter results in forbidden characters: "(", ")", ".", ",", and " ".

If, on the other hand, the parameter prints easily into an acceptable string, such as
a single integer like in this example:

```c++
using EncoderFrameSize = TestWithParam<uint32_t>;
TEST_P(EncoderFrameSize, FrameSizeOkay)
{
    EXPECT_NO_THROW(ADPCMEncoder(chrono::milliseconds(GetParam())));
}

INSTANTIATE_TEST_CASE_P(ADPCMEncoder, EncoderFrameSize, Values(1, 5, 10, 20));
```

Which produces the following test names that don't convey much meaning:

```
[----------] 4 tests from ADPCMEncoder/EncoderFrameSize
[ RUN      ] ADPCMEncoder/EncoderFrameSize.FrameSizeOkay/0
[       OK ] ADPCMEncoder/EncoderFrameSize.FrameSizeOkay/0 (0 ms)
[ RUN      ] ADPCMEncoder/EncoderFrameSize.FrameSizeOkay/1
[       OK ] ADPCMEncoder/EncoderFrameSize.FrameSizeOkay/1 (0 ms)
[ RUN      ] ADPCMEncoder/EncoderFrameSize.FrameSizeOkay/2
[       OK ] ADPCMEncoder/EncoderFrameSize.FrameSizeOkay/2 (0 ms)
[ RUN      ] ADPCMEncoder/EncoderFrameSize.FrameSizeOkay/3
[       OK ] ADPCMEncoder/EncoderFrameSize.FrameSizeOkay/3 (0 ms)
[----------] 4 tests from ADPCMEncoder/EncoderFrameSize (0 ms total)
```

Then by passing `PrintToStringParamName` to `INSTANTIATE_TEST_CASE_P` we can improve
the test names:

```c++
INSTANTIATE_TEST_CASE_P(ADPCMEncoder, EncoderFrameSize, Values(1, 5, 10, 20), PrintToStringParamName);
```

```
[----------] 4 tests from ADPCMEncoder/EncoderFrameSize
[ RUN      ] ADPCMEncoder/EncoderFrameSize.FrameSizeOkay/1
[       OK ] ADPCMEncoder/EncoderFrameSize.FrameSizeOkay/1 (0 ms)
[ RUN      ] ADPCMEncoder/EncoderFrameSize.FrameSizeOkay/5
[       OK ] ADPCMEncoder/EncoderFrameSize.FrameSizeOkay/5 (0 ms)
[ RUN      ] ADPCMEncoder/EncoderFrameSize.FrameSizeOkay/10
[       OK ] ADPCMEncoder/EncoderFrameSize.FrameSizeOkay/10 (0 ms)
[ RUN      ] ADPCMEncoder/EncoderFrameSize.FrameSizeOkay/20
[       OK ] ADPCMEncoder/EncoderFrameSize.FrameSizeOkay/20 (0 ms)
[----------] 4 tests from ADPCMEncoder/EncoderFrameSize (0 ms total)
```

Now the suffix is no longer an incrementing counter (0, 1, 2, 3) but instead the actual
FrameSize value being tested (1, 5, 10, 20).

When we cannot use`PrintToStringParamName` such as the QualityTest we can write our own function
that derives a name based on the inputs.  In some situations even that is inadequate as the inputs,
once stripped of invalid characters, is no longer unique.  The TrimTest is in this situation as
every test would be named "trimmed" and convey even less information than the mere counter.  In
this situation we could introduce an additional value to the inputs which is used for the test name
but not used in the test itself.

If we take that approach with the TrimTest example, it becomes this:

```
class TrimTest : public TestWithParam<tuple<string, string>>
{
public:
    const string& value()
    {
        return get<0>(GetParam());
    }

    static string name(const TestParamInfo<tuple<string, string>>& param)
    {
        return get<1>(param.param);
    }
};

TEST_P(TrimTest, Whitespace)
{
    ASSERT_THAT(stringutils::trim(value()), StrEq("trimmed"));
}

INSTANTIATE_TEST_CASE_P(
  Trim, TrimTest,
  Values(
    make_tuple("  trimmed     ", "spaces"), make_tuple("trimmed", "nothingToTrim"),
    make_tuple("trimmed ", "trailingSpace"), make_tuple(" trimmed", "leadingSpace"),
    make_tuple("\ntrimmed", "leadingNewline"), make_tuple("trimmed\n", "trailingNewline"),
    make_tuple("\ttrimmed", "leadingTab"), make_tuple("trimmed\t", "trailingTab"), make_tuple("\rtrimmed", "leadingCR"),
    make_tuple("trimmed\r", "trailingCR"), make_tuple("\r\t\n trimmed \r\t\n", "mixedWhitespace"),
    make_tuple("\r\rtrimmed\n\n", "repeatedCRandLF")), TrimTest::name);
```

And produces the following test names:

```
[----------] 12 tests from Trim/TrimTest
[ RUN      ] Trim/TrimTest.Whitespace/spaces
[       OK ] Trim/TrimTest.Whitespace/spaces (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/nothingToTrim
[       OK ] Trim/TrimTest.Whitespace/nothingToTrim (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/trailingSpace
[       OK ] Trim/TrimTest.Whitespace/trailingSpace (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/leadingSpace
[       OK ] Trim/TrimTest.Whitespace/leadingSpace (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/leadingNewline
[       OK ] Trim/TrimTest.Whitespace/leadingNewline (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/trailingNewline
[       OK ] Trim/TrimTest.Whitespace/trailingNewline (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/leadingTab
[       OK ] Trim/TrimTest.Whitespace/leadingTab (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/trailingTab
[       OK ] Trim/TrimTest.Whitespace/trailingTab (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/leadingCR
[       OK ] Trim/TrimTest.Whitespace/leadingCR (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/trailingCR
[       OK ] Trim/TrimTest.Whitespace/trailingCR (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/mixedWhitespace
[       OK ] Trim/TrimTest.Whitespace/mixedWhitespace (0 ms)
[ RUN      ] Trim/TrimTest.Whitespace/repeatedCRandLF
[       OK ] Trim/TrimTest.Whitespace/repeatedCRandLF (0 ms)
[----------] 12 tests from Trim/TrimTest (1 ms total)
```

Multiple Tests
--------------

Our examples thus far have contained a single test that was instantiated with multiple inputs.
The GTest structure where the _fixture_ is instantiated with various inputs means we can write
as many `TEST_P(FixtureName, …)` as we desire.  This provides an entire test _suite_ that we
run each input against.  This becomes more valuable as the unit under test becomes more complex.

An EDID parser would be a good example where a suite of tests can be built up, and when a
problematic EDID is discovered in the wild it can be added to the list of inputs to have every
test run with the problematic EDID.

For our example here we'll create a test that verifies specifically that `adjustQuality` is
successful:

```c++
TEST_P(ADPCMEncoderQualityTest, AdjustQuality)
{
    EXPECT_THAT(m_uut.adjustQuality(m_bandwidthActive, m_bandwidthLimit, m_queueFillRatio), Eq(true));
}
```

With no other change, the resulting tests become:

```
[----------] 18 tests from ADPCMEncoder/ADPCMEncoderQualityTest
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.AdjustQuality/0
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.AdjustQuality/0 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.AdjustQuality/1
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.AdjustQuality/1 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.AdjustQuality/2
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.AdjustQuality/2 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.AdjustQuality/3
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.AdjustQuality/3 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.AdjustQuality/4
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.AdjustQuality/4 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.AdjustQuality/5
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.AdjustQuality/5 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.AdjustQuality/6
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.AdjustQuality/6 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.AdjustQuality/7
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.AdjustQuality/7 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.AdjustQuality/8
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.AdjustQuality/8 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/0
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/0 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/1
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/1 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/2
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/2 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/3
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/3 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/4
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/4 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/5
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/5 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/6
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/6 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/7
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/7 (0 ms)
[ RUN      ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/8
[       OK ] ADPCMEncoder/ADPCMEncoderQualityTest.calculatesCorrectQuality/8 (0 ms)
[----------] 18 tests from ADPCMEncoder/ADPCMEncoderQualityTest (0 ms total)
```

GTest will run every test with every input.  This can quickly become a lot of tests.

Test Multiple Implementations (Abstract Tests)
----------------------------------------------

Up until now we've tested a single implementation.  When there are multiple subclasses
of a given interface, it can be desirable to have a set of standard tests that each
implementation must pass.  Individual subclasses may have additional tests that validate
behaviour specific to that subclass.  Those are normal tests that we've seen in previous
chapters.  The standard tests that all subclasses must pass are a prime example of
parameterized tests.  In fact, the interface definition may very well want to also provide
the test suite for future implementations that haven't even been written yet and won't
even reside in the same directory.  Tests like this are called Abstract Tests in GTest-speak.

We start with an interface that we will be testing against.  This may be a pure
interface or merely a base class.  We'll call ours VideoDriver;

```c++
class VideoDriver {
public:
    virtual ~VideoDriver() = default;

    virtual bool setTopology(size_t width, size_t height) = 0;
    virtual bool addMonitor() = 0;
};
```

Using this abstract class we can define abstract tests (and call it abstract art):

```c++
using VideoDriverCreator = std::function<std::unique_ptr<VideoDriver>()>;

class VideoDriverConformance : public ::testing::TestWithParam<VideoDriverCreator>
{
public:
    VideoDriverConformance();

    std::unique_ptr<VideoDriver> m_uut;
};
```

This parameterized test fixture is placed in a header file that tests for derived
classes can access.  The test parameter is a factory function so that authors of
the derived classes can provide instances of their own implementation.

Elsewhere in a `.cpp` file that is built into a library we define the actual tests,
without knowing what concrete class will be under test:

```c++
VideoDriverConformance::VideoDriverConformance()
  : m_uut(GetParam()())
{
}

TEST_P(VideoDriverConformance, BasicTopology)
{
    EXPECT_THAT(m_uut->setTopology(640, 480), Eq(true));
}

TEST_P(VideoDriverConformance, AddMonitor)
{
    EXPECT_THAT(m_uut->addMonitor(), Eq(true));
}
```

Now an implementation of VideoDriver can create a test with the following contents:

```c++
namespace
{
unique_ptr<VideoDriver> createDriver()
{
    return unique_ptr<VideoDriver>(new AMDVideoDriver());
}
}  // namespace

INSTANTIATE_TEST_CASE_P(AMD, VideoDriverConformance, Values(createDriver));
```

This defines a factory function specific to this particular implementation and then
instantiates the entire suite of tests (whatever they may be).

There is a small snag.  The definition of the test suite has been done in a library,
not visible to this code to be executed.  If that library is a static library, then some
compilers may optimize out the tests believing that the code is unused.  If the library is
a shared library then they are not optimized out.  Instead we have DLL Hell on Windows.
A compromise to keep with static libraries (for the sake of Windows) while not losing
the tests is to force a test definition _in the .cpp file instantiating the tests_.

To do that we'll add the following:

```
// This is required to defeat optimizing compilers; I.e. this makes it clear to the compiler
// that VideoDriverConformance IS used and shouldn't be cut out.
TEST_P(VideoDriverConformance, ForceSuiteToLoad) {}
```

With that out of the way when we run the test for AMD we magically get the following
tests:

```
[----------] 3 tests from AMD/VideoDriverConformance
[ RUN      ] AMD/VideoDriverConformance.ForceSuiteToLoad/0
[       OK ] AMD/VideoDriverConformance.ForceSuiteToLoad/0 (0 ms)
[ RUN      ] AMD/VideoDriverConformance.BasicTopology/0
[       OK ] AMD/VideoDriverConformance.BasicTopology/0 (0 ms)
[ RUN      ] AMD/VideoDriverConformance.AddMonitor/0
[       OK ] AMD/VideoDriverConformance.AddMonitor/0 (0 ms)
[----------] 3 tests from AMD/VideoDriverConformance (0 ms total)
```

If another test is added to the suite afterwards, it will cause a re-linking of test
instantiating the suite and the new test will be run with no change to the derived
class' test.

```
[----------] 4 tests from AMD/VideoDriverConformance
[ RUN      ] AMD/VideoDriverConformance.ForceSuiteToLoad/0
[       OK ] AMD/VideoDriverConformance.ForceSuiteToLoad/0 (0 ms)
[ RUN      ] AMD/VideoDriverConformance.BasicTopology/0
[       OK ] AMD/VideoDriverConformance.BasicTopology/0 (0 ms)
[ RUN      ] AMD/VideoDriverConformance.AddMonitor/0
[       OK ] AMD/VideoDriverConformance.AddMonitor/0 (0 ms)
[ RUN      ] AMD/VideoDriverConformance.AddTwoMonitors/0
[       OK ] AMD/VideoDriverConformance.AddTwoMonitors/0 (0 ms)
[----------] 4 tests from AMD/VideoDriverConformance (0 ms total)
```

When another implementation is written, it too can be run against the exact same test
suite (current and future) with the same somewhat-boilerplate code.  When instantiating
the test suite be sure to use a unique prefix.

```
namespace
{
unique_ptr<VideoDriver> createDriver()
{
    return unique_ptr<VideoDriver>(new NvidiaVideoDriver());
}
}  // namespace

// This is required to defeat optimizing compilers; I.e. this forces the other test cases defined in
// an external library to be linked in.
TEST_P(VideoDriverConformance, ForceSuiteToLoad) {}

INSTANTIATE_TEST_CASE_P(Nvidia, VideoDriverConformance, Values(createDriver));
```

```
[----------] 4 tests from Nvidia/VideoDriverConformance
[ RUN      ] Nvidia/VideoDriverConformance.ForceSuiteToLoad/0
[       OK ] Nvidia/VideoDriverConformance.ForceSuiteToLoad/0 (0 ms)
[ RUN      ] Nvidia/VideoDriverConformance.BasicTopology/0
[       OK ] Nvidia/VideoDriverConformance.BasicTopology/0 (0 ms)
[ RUN      ] Nvidia/VideoDriverConformance.AddMonitor/0
[       OK ] Nvidia/VideoDriverConformance.AddMonitor/0 (0 ms)
[ RUN      ] Nvidia/VideoDriverConformance.AddTwoMonitors/0
[       OK ] Nvidia/VideoDriverConformance.AddTwoMonitors/0 (0 ms)
[----------] 4 tests from Nvidia/VideoDriverConformance (0 ms total)
```

Test Multiple Types (Typed Tests)
---------------------------------

So far so good if we have a shared base class.  There are times, however, when an API is adhered
to and behaviour is expected even though implementations do not share a base class.  This may be
for performance reasons, or because the class itself is a template.  For these needs we have Typed
Tests.

In this example we'll write a test for a container that can hold any type.  This container is a
template, so the various "instances" of the container do not share a common base class nor have
any virtual functions.  The example can also be adjusted to non-template types that conform to
an API such as conforming to _BasicLockable_ which `std::mutex` conforms to, but any user defined
class may also implement.  Or similarly algorithms implemented in SSE2 vs AVX vs C++ that are non
virtual, accept identical inputs and are expected to produce identical outputs.

This time when we define our test fixture (which as always must derive from `Test`) we make it a
template:

```c++
template<typename T>
class NotAVectorTest : public Test
{
public:
    NotAVector<T> m_uut;
};
```

Next up we declare what types we're going to use.  Unlike the inheritance example earlier where
the concrete types could be left unspecified and will be sorted out at runtime, we don't have
vtables at our disposal so this must all be sorted out at compile time.  If creating tests for
a concept and wanting each implementation to be able to "pick up" the test suite, you'll need to
go a little non-standard with the `#include` to first define the types and _then_ `#include` the
header containing the test suite.

In this example the test suite is only applicable to this module and so the list of types as well
as the test suite itself is all defined privately in the .cpp.

```c++
using ContentTypes = Types<char, size_t, Blob>;
TYPED_TEST_CASE(NotAVectorTest, ContentTypes);
```

The tests themselves use the macro `TYPED_TEST`.  It's not clear why it's not `TEST_T` to match
`TEST_F` and `TEST_P`.  That's just the way it is.

There are a few other caveats that are a result of the fact that the baseclass (our test fixture) is
now a template.

* The _type_ being parameterized is available via `TypeParam`
* Access to member variables or functions belonging to the test fixture must go through `this->`
  
```c++
TYPED_TEST(NotAVectorTest, StoreSingle)
{
    // TypeParam is the type for this run of the test
    TypeParam obj;

    // The base class is a template, so we must use this-> to access stuff from it.
    EXPECT_THAT(this->m_uut, IsEmpty());
    this->m_uut.push_back(obj);
    EXPECT_THAT(this->m_uut.size(), Eq(1));
}

TYPED_TEST(NotAVectorTest, StoreMultiple)
{
    TypeParam obj;

    EXPECT_THAT(this->m_uut, IsEmpty());
    this->m_uut.push_back(obj);
    EXPECT_THAT(this->m_uut.size(), Eq(1));
    this->m_uut.push_back(obj);
    EXPECT_THAT(this->m_uut.size(), Eq(2));
}
```

All of this combined results in the following tests:

```
[----------] 2 tests from NotAVectorTest/0, where TypeParam = char
[ RUN      ] NotAVectorTest/0.StoreSingle
[       OK ] NotAVectorTest/0.StoreSingle (0 ms)
[ RUN      ] NotAVectorTest/0.StoreMultiple
[       OK ] NotAVectorTest/0.StoreMultiple (0 ms)
[----------] 2 tests from NotAVectorTest/0 (0 ms total)

[----------] 2 tests from NotAVectorTest/1, where TypeParam = unsigned long
[ RUN      ] NotAVectorTest/1.StoreSingle
[       OK ] NotAVectorTest/1.StoreSingle (0 ms)
[ RUN      ] NotAVectorTest/1.StoreMultiple
[       OK ] NotAVectorTest/1.StoreMultiple (0 ms)
[----------] 2 tests from NotAVectorTest/1 (0 ms total)

[----------] 2 tests from NotAVectorTest/2, where TypeParam = (anonymous namespace)::Blob
[ RUN      ] NotAVectorTest/2.StoreSingle
[       OK ] NotAVectorTest/2.StoreSingle (0 ms)
[ RUN      ] NotAVectorTest/2.StoreMultiple
[       OK ] NotAVectorTest/2.StoreMultiple (0 ms)
[----------] 2 tests from NotAVectorTest/2 (0 ms total)
```

General Recommendations
-----------------------

* Execution time becomes even more critical as the number of tests explode
* Use parameterized tests when there are multiple tests that otherwise do the same thing
  * This scales better when adding a new input
  * This makes it clear to humans that the code itself is in fact identical
* Use parameterized tests when creating a test suite for multiple implementations
  * eg: for multiple derived classes
  * eg: for multiple implementations of an interface (ie: SSE2, AVX, C++, …)
