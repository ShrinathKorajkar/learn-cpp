Chapter 5 - Custom Matchers
===========================

Key Concepts
------------

* Simple matchers
* Parameterized matchers
* Nested matchers

When Free Isn't Good Enough
---------------------------

GMock provides many matchers for us to use.  They cover many common needs from numbers
to strings to containers and more.  But sometimes we want to test something that isn't
available or stringing the necessary matchers together hinders readability of the test.

GMock provides the ability for us to define our own matchers so that we can have a
custom fit.

Matcher Basics
--------------

### Does It Match

The simplest of matchers validate a given value and reports whether it matched its
criteria or not.  Consider the scenario where it would be an error for imaging code
to set a topology with a non-even number of pixels.  GMock does not provide a matcher
out of the box for testing whether a value is even or not.  So let's write one.

```c++
class IsEvenMatcher : public MatcherInterface<size_t> {
 public:
  bool MatchAndExplain(size_t n, MatchResultListener* listener) const override {
    return (n % 2) == 0;
  }

  void DescribeTo(std::ostream* os) const override {}
};

inline Matcher<size_t> IsEven() {
    return MakeMatcher(new IsEvenMatcher());
}
```

To create a matcher we inherit from `MatcherInterface` and implement two methods.
`MatchAndExplain` is the crux of a matcher.  It must return `true` for a match
and `false` if it doesn't match.  We'll get to the `AndExplain` part and
`DescribeTo` shortly.

The name of the class should not be exactly the name that tests will use, because
tests must go through a factory function in order to obtain a matcher instance.
GMock does this deliberately for ownership and copying reasons, as well as to
permit us to write `EXPECT_CALL(foo, bar(IsEven()));` instead of forcing every caller
to write `EXPECT_CALL(foo, bar(Eq(IsEven())));`.  The factory function should be
named exactly as tests will refer to the matcher.

With the above code we can now write a test that succinctly tests for even-ness of
any given value.

```c++
TEST_F(TopologyTest, WidthRoundsToEven)
{
    EXPECT_CALL(m_listener, Call(Not(IsEven()), _));
    m_topology.requestTopology(1023, 2001);
}
```

As is typical, there is no output when things are good.  The test quietly passes.
However when the validation fails we receive the following output:

```
[ RUN      ] TopologyTest.WidthRoundsToEven
unknown file: Failure

Unexpected mock function call - returning directly.
    Function call: Call(1023, 2001)
Google Mock tried the following 1 expectation, but it didn't match:

../../topology/src/test/test_topology.cpp:25: EXPECT_CALL(m_listener, Call(IsEven(), _))...
  Expected arg #0: 
           Actual: 1023
         Expected: to be called once
           Actual: never called - unsatisfied and active
../../topology/src/test/test_topology.cpp:25: Failure
Actual function call count doesn't match EXPECT_CALL(m_listener, Call(IsEven(), _))...
         Expected: to be called once
           Actual: never called - unsatisfied and active
[  FAILED  ] TopologyTest.WidthIsEven (1 ms)
```

### Useful Diagnostic Messages

The previous error message is less than helpful, because `Expected arg #0` doesn't
tell us what was expected, so we don't know why the actual value is not good enough.
`DescribeTo` allows us to describe our matcher in diagnostics.

```c++
  void DescribeTo(std::ostream* os) const override {
    *os << "is even";
  }
```

The `ostream` is guaranteed to not be null.  The string should be a verb phrase
describing the property being tested.  Now the same failure produces this output:

```
[ RUN      ] TopologyTest.WidthRoundsToEven
unknown file: Failure

Unexpected mock function call - returning directly.
    Function call: Call(1023, 2001)
Google Mock tried the following 1 expectation, but it didn't match:

../../topology/src/test/test_topology.cpp:25: EXPECT_CALL(m_listener, Call(IsEven(), _))...
  Expected arg #0: is even
           Actual: 1023
         Expected: to be called once
           Actual: never called - unsatisfied and active
../../topology/src/test/test_topology.cpp:25: Failure
Actual function call count doesn't match EXPECT_CALL(m_listener, Call(IsEven(), _))...
         Expected: to be called once
           Actual: never called - unsatisfied and active
[  FAILED  ] TopologyTest.WidthIsEven (0 ms)
```

From this message we can see that argument 0 was expected to be even, but in fact
the value was 1023, which is an odd number.

### Nicer diagnostic messages for negative matches

While we _could_ write an `IsOdd` matcher to pair with `IsEven`, that duplicates
work.  To make such duplication unnecessary, GMock provides the `Not()` matcher.
Used together with our `IsEven` we can match an even number or an uneven number.

```c++
TEST_F(TopologyTest, HeightIsNotEven)
{
    EXPECT_CALL(m_listener, Call(_, Not(IsEven())));
    m_topology.requestTopology(1023, 2000);
}
```

When we negate the matcher in this way, the error message becomes:

```
[ RUN      ] TopologyTest.HeightIsNotEven
unknown file: Failure

Unexpected mock function call - returning directly.
    Function call: Call(1023, 2000)
Google Mock tried the following 1 expectation, but it didn't match:

../../topology/src/test/test_topology.cpp:31: EXPECT_CALL(m_listener, Call(_, Not(IsEven())))...
  Expected arg #1: not (is even)
           Actual: 2000
         Expected: to be called once
           Actual: never called - unsatisfied and active
../../topology/src/test/test_topology.cpp:31: Failure
Actual function call count doesn't match EXPECT_CALL(m_listener, Call(_, Not(IsEven())))...
         Expected: to be called once
           Actual: never called - unsatisfied and active
[  FAILED  ] TopologyTest.HeightIsNotEven (0 ms)
```

With only a few lines of code we can improve the grammar of "Expected: not (is even)".
Our matcher class may override `DescribeNegationTo` alongside `DescribeTo`:

```c++
  void DescribeNegationTo(std::ostream* os) const override {
    *os << "isn't even";
  }
```

With this small change, the failure message is easier to read:

```
[ RUN      ] TopologyTest.HeightIsNotEven
unknown file: Failure

Unexpected mock function call - returning directly.
    Function call: Call(1023, 2000)
Google Mock tried the following 1 expectation, but it didn't match:

../../topology/src/test/test_topology.cpp:31: EXPECT_CALL(m_listener, Call(_, Not(IsEven())))...
  Expected arg #1: isn't even
           Actual: 2000
         Expected: to be called once
           Actual: never called - unsatisfied and active
../../topology/src/test/test_topology.cpp:31: Failure
Actual function call count doesn't match EXPECT_CALL(m_listener, Call(_, Not(IsEven())))...
         Expected: to be called once
           Actual: never called - unsatisfied and active
[  FAILED  ] TopologyTest.HeightIsNotEven (0 ms)
```

### Now With Less Code

To reduce the amount of code needed to write a custom matcher even further, GMock
provides a macro `MATCHER` that takes a name, a description, and allows you to
fill in the body of `MatchAndExplain` with the first argument (the value to match)
provided under the name `arg`.  It then handles the class boilerplate and factory function.

We can rewrite the `IsEven` matcher concisely using the macro:

```c++
MATCHER(IsEven, "is even")
{
    return (arg % 2) == 0;
}
```

To bring it up to par with our previous implementation we need to adjust the
description to have a nice negated variant.  The macro provides a boolean variable
`negation` that we can access in the description field to create the description
string for either positive or negative cases:

```c++
MATCHER(IsEven, negation ? "isn't even" : "is even")
{
    return (arg % 2) == 0;
}
```

Parameterized Matchers
----------------------

Fixed matchers are perfect for certain comparisons.  Other comparisons are much
more flexible if they allow some level of control by the invoker.  Consider a restriction
where the height of a display must be a multiple of 4 (nvidia I'm looking at you).
Rather than write a fixed matcher for `IsMultipleOf4`, we can instead write a generic matcher
for `IsMultipleOf` and leave it to the caller to specify the specific multiple while maintaining
the same level of readability.

The `MATCHER` macro has counterparts to handle creating matchers that accept parameters.
They are named `MATCHER_P` for a single parameter and `MATCHER_P#` where `#` is the number
of parameters for the matcher for 2+ parameters.

```c++
MATCHER_P(IsMultipleOf, value, string(negation ? "isn't" : "is") + " a multiple of " + PrintToString(value))
{
    return (arg % value) == 0;
}
```

Parameters are named in the macro after the name and before the description.
They are then able to be referenced in both the body of the matcher as well as the
description string.  `PrintToString` is a function provided by GMock that formats
a wide variety of types.

Using a parameterized matcher is very similar to our earlier fixed matcher:

```c++
TEST_F(TopologyTest, HeightIsMultipleOf8)
{
    EXPECT_CALL(m_listener, Call(_, IsMultipleOf(8)));
    m_topology.requestTopology(1023, 1062);
}
```

The diagnostic messages provided are also similar:

```
[ RUN      ] TopologyTest.HeightIsMultipleOf8
unknown file: Failure

Unexpected mock function call - returning directly.
    Function call: Call(1023, 1062)
Google Mock tried the following 1 expectation, but it didn't match:

../../topology/src/test/test_topology.cpp:37: EXPECT_CALL(m_listener, Call(_, IsMultipleOf(8)))...
  Expected arg #1: is a multiple of 8
           Actual: 1062
         Expected: to be called once
           Actual: never called - unsatisfied and active
../../topology/src/test/test_topology.cpp:37: Failure
Actual function call count doesn't match EXPECT_CALL(m_listener, Call(_, IsMultipleOf(8)))...
         Expected: to be called once
           Actual: never called - unsatisfied and active
[  FAILED  ] TopologyTest.HeightIsMultipleOf8 (0 ms)
```

### Improved Diagnostic Messages

When a match failed with `IsEven`, it's pretty clear to see that a number is or is not even.
When we begin using less trivial values, especially uncontrolled values that can be provided
by individual tests, then eyeballing that "oh of course 12345 is not a multiple of 85" is not
as easy.  Matchers have the ability to _explain_ their match.

In the original class we saw at the beginning, the function `MatchAndExplain` takes a
`MatchResultListener*` as its second argument.  This pointer is guaranteed to not be null by
GMock and provides a `<<` operator where the matcher can explain the situation.

When using the `MATCHER*` macros, this parameter is available by the name `result_listener`.

```c++
MATCHER_P(IsMultipleOf, value, string(negation ? "isn't" : "is") + " a multiple of " + PrintToString(value))
{
    auto remainder = arg % value;
    if( remainder ) {
        *result_listener << "the remainder is " << remainder;
    }
    return remainder == 0;
}
```

The diagnostics now contain a little more detail on the matter.

```
[ RUN      ] TopologyTest.HeightIsMultipleOf8
unknown file: Failure

Unexpected mock function call - returning directly.
    Function call: Call(1023, 1062)
Google Mock tried the following 1 expectation, but it didn't match:

../../topology/src/test/test_topology.cpp:37: EXPECT_CALL(m_listener, Call(_, IsMultipleOf(8)))...
  Expected arg #1: is a multiple of 8
           Actual: 1062, the remainder is 6
         Expected: to be called once
           Actual: never called - unsatisfied and active
../../topology/src/test/test_topology.cpp:37: Failure
Actual function call count doesn't match EXPECT_CALL(m_listener, Call(_, IsMultipleOf(8)))...
         Expected: to be called once
           Actual: never called - unsatisfied and active
[  FAILED  ] TopologyTest.HeightIsMultipleOf8 (0 ms)
```

It's important to realize that diagnostic message are not only issued for failed matches,
but may be issued for _successful_ matches if the match has been negated.

```c++
TEST_F(TopologyTest, HeightIsNotAMultipleOf12)
{
    EXPECT_CALL(m_listener, Call(_, Not(IsMultipleOf(12))));
    m_topology.requestTopology(1023, 1068);
}
```

```
[ RUN      ] TopologyTest.HeightIsNotAMultipleOf12
unknown file: Failure

Unexpected mock function call - returning directly.
    Function call: Call(1023, 1068)
Google Mock tried the following 1 expectation, but it didn't match:

../../topology/src/test/test_topology.cpp:43: EXPECT_CALL(m_listener, Call(_, Not(IsMultipleOf(12))))...
  Expected arg #1: isn't a multiple of 12
           Actual: 1068
         Expected: to be called once
           Actual: never called - unsatisfied and active
../../topology/src/test/test_topology.cpp:43: Failure
Actual function call count doesn't match EXPECT_CALL(m_listener, Call(_, Not(IsMultipleOf(12))))...
         Expected: to be called once
           Actual: never called - unsatisfied and active
[  FAILED  ] TopologyTest.HeightIsNotAMultipleOf12 (0 ms)
```

Where it makes sense, issue an explanation for both successful and unsuccessful matches.

```c++
MATCHER_P(IsMultipleOf, value, string(negation ? "isn't" : "is") + " a multiple of " + PrintToString(value))
{
    auto remainder = arg % value;
    if( remainder ) {
        *result_listener << "the remainder is " << remainder;
    } else {
        *result_listener << "which is an even multiple of " << PrintToString(value);
    }
    return remainder == 0;
}
```

```
[ RUN      ] TopologyTest.HeightIsNotAMultipleOf12
unknown file: Failure

Unexpected mock function call - returning directly.
    Function call: Call(1023, 1068)
Google Mock tried the following 1 expectation, but it didn't match:

../../topology/src/test/test_topology.cpp:43: EXPECT_CALL(m_listener, Call(_, Not(IsMultipleOf(12))))...
  Expected arg #1: isn't a multiple of 12
           Actual: 1068, which is an even multiple of 12
         Expected: to be called once
           Actual: never called - unsatisfied and active
../../topology/src/test/test_topology.cpp:43: Failure
Actual function call count doesn't match EXPECT_CALL(m_listener, Call(_, Not(IsMultipleOf(12))))...
         Expected: to be called once
           Actual: never called - unsatisfied and active
[  FAILED  ] TopologyTest.HeightIsNotAMultipleOf12 (0 ms)
```

Matchers Inside Matchers
------------------------

Matches themselves are templated types.  To accept another matcher as a parameter, we require a
templated class.  There is no `MATCHER` macro to help us, but there are other helpers that reduce
the necessary boilerplate.

### Simple passthrough

A matcher that takes a numeric value, evaluates it modulo 2, then passes the remainder to another
matcher looks like this:

```c++
template<typename T>
class Modulo2Matcher
{
public:
    Modulo2Matcher(const Matcher<const T&>& matcher)
      : m_matcher(matcher)
    {
    }

    void DescribeTo(std::ostream* os) const
    {
        *os << "is a number whose remainder modulo 2 ";
        m_matcher.DescribeTo(os);
    }

    void DescribeNegationTo(std::ostream* os) const
    {
        *os << "is a number whose remainder modulo 2 ";
        m_matcher.DescribeNegationTo(os);
    }

    template<typename Arg>
    bool MatchAndExplain(const Arg& value, MatchResultListener* listener) const
    {
        *listener << "whose remainder modulo 2 is ";
        auto modulo = value % 2;
        return MatchPrintAndExplain(modulo, m_matcher, listener);
    }

    const Matcher<const T&> m_matcher;

    GTEST_DISALLOW_ASSIGN_(Modulo2Matcher);
};

template<typename Matcher>
inline PolymorphicMatcher<Modulo2Matcher<size_t>> Modulo2(const Matcher& matcher)
{
    return MakePolymorphicMatcher(Modulo2Matcher<size_t>(matcher));
}
```

The above has a similar structure to the original `IsEvenMatcher` we wrote earlier.  This time
we do not inherit from `MatcherInterface<>`.  The functions `DescribeTo`,`DescribeNegationTo`
and `MatchAndExplain` match the same signature.  But this time they are not overriding a
base class functions and `MatchAndExplain` is itself a templated function.  The template
type is the argument type.  ie: in `EXPECT_THAT(foo, MyMatcher(OtherMatcher()))`, it represents
the type of `foo`.  The class overall is templated on the type of matcher that will be provided.
ie: the template argument of `OtherMatcher` in the previous example.

The factory function to instantiate this type of matcher uses `MakePolymorphicMatcher` rather
than the `MakeMatcher` we saw earlier.

The implementations of the describe functions pass through to the nested matcher so that the
diagnostic message is as clear as possible.

Similarly, the `MatchAndExplain` does its own processing (computing the modulus) and explains
its processing to the listener before handing the converted value to be processed by the
nested matcher.  `MatchPrintAndExplain` is provided by GMock and will:
 * Print the value being matched (first argument).  This is why the explanation to the listener
 stops short of streaming the value.
 * Evaluate `MatchAndExplain` of the nested matcher.
 * If the nested matcher had anything to explain, then concatenate the messages together with
 a comma separating them.

The above matcher can now be used anywhere a matcher is accepted, including Mock call expectations
or inline `EXPECT_THAT`/`ASSERT_THAT` calls.

```c++
TEST_F(TopologyTest, ModuloUnhappy)
{
    EXPECT_THAT(123, Modulo2(Eq(0)));
    EXPECT_THAT(124, Modulo2(Not(Eq(0))));
    EXPECT_THAT(123, Modulo2(IsEven()));
    EXPECT_THAT(124, Modulo2(Not(IsMultipleOf(4))));
}
```

Both the _Expected_ and _Actual_ diagnostic messages combine the descriptions from the entire
chain of matchers.

```
[ RUN      ] TopologyTest.ModuloUnhappy
../../topology/src/test/test_topology.cpp:68: Failure
Value of: 123
Expected: is a number whose remainder modulo 2 is equal to 0
  Actual: 123 (of type int), whose remainder modulo 2 is 1 (of type int)
../../topology/src/test/test_topology.cpp:69: Failure
Value of: 124
Expected: is a number whose remainder modulo 2 isn't equal to 0
  Actual: 124 (of type int), whose remainder modulo 2 is 0 (of type int)
../../topology/src/test/test_topology.cpp:70: Failure
Value of: 123
Expected: is a number whose remainder modulo 2 is even
  Actual: 123 (of type int), whose remainder modulo 2 is 1 (of type int)
../../topology/src/test/test_topology.cpp:71: Failure
Value of: 124
Expected: is a number whose remainder modulo 2 isn't a multiple of 4
  Actual: 124 (of type int), whose remainder modulo 2 is 0 (of type int), which is an even multiple of 4
[  FAILED  ] TopologyTest.ModuloUnhappy (0 ms)
```

### Multiple Parameters

Polymorphic matchers such as `Modulo2` are not restricted to only accepting a matcher.  We can
generalize `Modulo2` into a `Modulo` matcher that will compute the remainder of whatever modulus
it is given.

```c++
template<typename T>
class ModuloMatcher
{
public:
    ModuloMatcher(size_t modulus, const Matcher<const T&>& matcher)
      : m_modulus(modulus)
      , m_matcher(matcher)
    {
    }

    void DescribeTo(std::ostream* os) const
    {
        *os << "is a number whose remainder modulo " << to_string(m_modulus) << " ";
        m_matcher.DescribeTo(os);
    }

    void DescribeNegationTo(std::ostream* os) const
    {
        *os << "is a number whose remainder modulo " << to_string(m_modulus) << " ";
        m_matcher.DescribeNegationTo(os);
    }

    template<typename Arg>
    bool MatchAndExplain(const Arg& value, MatchResultListener* listener) const
    {
        *listener << "whose remainder modulo " << to_string(m_modulus) << " is ";
        auto modulo = value % m_modulus;
        return MatchPrintAndExplain(modulo, m_matcher, listener);
    }

    const size_t m_modulus;
    const Matcher<const T&> m_matcher;

    GTEST_DISALLOW_ASSIGN_(ModuloMatcher);
};

template<typename Matcher>
inline PolymorphicMatcher<ModuloMatcher<size_t>> Modulo(size_t modulus, const Matcher& matcher)
{
    return MakePolymorphicMatcher(ModuloMatcher<size_t>(modulus, matcher));
}
```

This more generic variant is used similarly:

```c++
TEST_F(TopologyTest, ModuloUnhappy)
{
    EXPECT_THAT(123, Modulo(5, Lt(2)));
    EXPECT_THAT(124, Modulo(7, Not(Eq(5))));
    EXPECT_THAT(123, Modulo(11, Not(IsEven())));
    EXPECT_THAT(124, Modulo(13, IsMultipleOf(4)));
}
```

And produces similar diagnostic messages:

```
[ RUN      ] TopologyTest.ModuloUnhappy
../../topology/src/test/test_topology.cpp:74: Failure
Value of: 123
Expected: is a number whose remainder modulo 5 is < 2
  Actual: 123 (of type int), whose remainder modulo 5 is 3 (of type unsigned long)
../../topology/src/test/test_topology.cpp:75: Failure
Value of: 124
Expected: is a number whose remainder modulo 7 isn't equal to 5
  Actual: 124 (of type int), whose remainder modulo 7 is 5 (of type unsigned long)
../../topology/src/test/test_topology.cpp:76: Failure
Value of: 123
Expected: is a number whose remainder modulo 11 isn't even
  Actual: 123 (of type int), whose remainder modulo 11 is 2 (of type unsigned long)
../../topology/src/test/test_topology.cpp:77: Failure
Value of: 124
Expected: is a number whose remainder modulo 13 is a multiple of 4
  Actual: 124 (of type int), whose remainder modulo 13 is 7 (of type unsigned long), the remainder is 3
[  FAILED  ] TopologyTest.ModuloUnhappy (0 ms)
```

General Recommendations
-----------------------

* If you need a matcher that seems basic/common, first check whether GMock provides it
* Use the `MATCHER*` macros to succinctly create custom matchers to improve readability of tests
* Write an appropriate description of the matcher for clarity
* For trivial matchers, do _not_ describe the match to the listener (it just adds noise)
* For non-trivial matchers, _do_ describe the match to the listener to assist in the analysis
