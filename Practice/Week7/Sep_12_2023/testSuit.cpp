#include <iostream>
#include <gtest/gtest.h>
/*
    TEST_F()    - suits with fixture
    TEST()      - suits w/o fixture
*/
TEST(StringManipulationTestSuite, Concatenation)
{
    std::string str1 = "Hello, ";
    std::string str2 = "World!";
    std::string result = str1 + str2;
    ASSERT_EQ(result, "Hello, World!");
}

TEST(StringManipulationTestSuite, Length)
{
    std::string str = "Google Test";
    ASSERT_EQ(str.length(), 11);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
