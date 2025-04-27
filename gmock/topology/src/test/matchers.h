#pragma once

#include <gmock/gmock.h>

#include <string>

using namespace std;
using namespace testing;

#if 0
class IsEvenMatcher : public MatcherInterface<size_t>
{
public:
    bool MatchAndExplain(size_t n, MatchResultListener* listener) const override
    {
        return (n % 2) == 0;
    }

    void DescribeTo(std::ostream* os) const override
    {
        *os << "is even";
    }

    void DescribeNegationTo(std::ostream* os) const override
    {
        *os << "isn't even";
    }
};

inline Matcher<size_t> IsEven()
{
    return MakeMatcher(new IsEvenMatcher());
}
#else
MATCHER(IsEven, negation ? "isn't even" : "is even")
{
    return (arg % 2) == 0;
}
#endif

MATCHER_P(IsMultipleOf, value, string(negation ? "isn't" : "is") + " a multiple of " + PrintToString(value))
{
    auto remainder = arg % value;
    if (remainder) {
        *result_listener << "the remainder is " << remainder;
    } else {
        *result_listener << "which is an even multiple of " << PrintToString(value);
    }
    return remainder == 0;
}

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
