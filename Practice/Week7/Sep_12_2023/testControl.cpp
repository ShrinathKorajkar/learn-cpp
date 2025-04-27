#include <iostream>
#include <gtest/gtest.h>
/*
    ./my_tests --gtest_filter=MyTestSuite.*
    ./my_tests --gtest_filter=MyTestSuite.MyTestCase
    ./my_tests --gtest_filter=*:fast

*/
TEST(MyCustomTest, DISABLED_disabledTest) { std::cout << "DISABLED" << std::endl; }

TEST(MyTestSuite, SkippedTest)
{
    GTEST_SKIP() << "This test is temporarily skipped.";
    int result = 2 + 3;
    EXPECT_EQ(result, 4);
}

TEST(MyTestSuite, PlaceholderTest)
{
    GTEST_SUCCEED() << "This test is a placeholder for future testing.";
    GTEST_FAIL() << "This test should fail.";
}

TEST(MyTestSuite, FailureWithLocation)
{
    GTEST_FAIL_AT(__FILE__, __LINE__) << "This test failed at a specific location.";
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}