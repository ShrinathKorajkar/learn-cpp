#include <iostream>
#include <gtest/gtest.h>

TEST(myTestSuit, testCase)
{
    const testing::TestInfo *const test_info =
        testing::UnitTest::GetInstance()->current_test_info();

    std::cout << "Test Info name : " << test_info->name() << std::endl;
    std::cout << "Test Info suit name : " << test_info->test_suite_name() << std::endl;
}

testing::AssertionResult isEven(const int &number)
{
    if (number % 2 == 0)
    {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure();
}

TEST(myTestSuit, tescase2)
{
    ASSERT_EQ(isEven(2), isEven(4));
}