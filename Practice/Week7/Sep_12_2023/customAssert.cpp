#include <iostream>
#include <gtest/gtest.h>

void AssertStringContainsSubstring(const std::string &str, const std::string &substr)
{
    ASSERT_TRUE(str.find(substr) != std::string::npos) << str << " String does not contain the substring: " << substr;
}

TEST(MyTest, StringContainsSubstring)
{
    std::string myString = "Hello, World!";
    AssertStringContainsSubstring(myString, "World");
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}