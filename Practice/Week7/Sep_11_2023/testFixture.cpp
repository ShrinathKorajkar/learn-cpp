#include <iostream>
#include <gtest/gtest.h>
/*
    Fixture Base classes:
    ::testing::Test
    ::testing::TestWithParam<T>
    ::testing::TestWithParamAndFixture<T>
    ::testing::TestSuite
    ::testing::TestSuiteWithParams
    ::testing::Environment
    ::testing::EnvironmentWithParam<T>
    ::testing::EmptyTestEventListener
    ::testing::SetUpTestSuite
    ::testing::TearDownTestSuite
*/

class Calculator
{
public:
    int add(int a, int b)
    {
        return a + b;
    }
    int subtract(int a, int b)
    {
        return a - b;
    }
};

class CalculatorTest : public ::testing::Test
{

protected:
    static int sharedResource;
    Calculator *calculator;
    void SetUp() override
    {
        calculator = new Calculator();
        sharedResource++;
    }

    void TearDown() override
    {
        delete calculator;
    }
};

int CalculatorTest::sharedResource = 0;

bool isEven(int num)
{
    return num % 2 == 0;
}

class IsEvenTest : public ::testing::TestWithParam<int>
{
};

bool isVowel(char c)
{
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

class IsVowelTest : public ::testing::TestWithParam<char>
{
};

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

//
//

TEST_F(CalculatorTest, AddTest)
{
    int result = calculator->add(2, 3);
    ASSERT_EQ(result, 5);
    CalculatorTest::sharedResource++;
}

TEST_F(CalculatorTest, SubtractTest)
{
    int result = calculator->subtract(2, 3);
    ASSERT_EQ(result, -1);
    std::cout << CalculatorTest::sharedResource << std::endl;
}

TEST_P(IsEvenTest, checkEven)
{
    int input = GetParam();
    ASSERT_TRUE(isEven(input)) << input << " should be even.";
}

TEST_P(IsVowelTest, checkVowel)
{
    char c = GetParam();
    EXPECT_TRUE(isVowel(c)) << c << " is not a vowel.";
}

INSTANTIATE_TEST_SUITE_P(ParamTest, IsEvenTest, ::testing::Values(2, 3, 4, 5, 6));
INSTANTIATE_TEST_SUITE_P(ParamTest, IsVowelTest, ::testing::Range('a', 'f'));
