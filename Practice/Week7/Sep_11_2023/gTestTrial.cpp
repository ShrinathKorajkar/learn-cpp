#include <gtest/gtest.h>

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

TEST(MyTest, TestCase1)
{
    ASSERT_EQ(1, 1);
}