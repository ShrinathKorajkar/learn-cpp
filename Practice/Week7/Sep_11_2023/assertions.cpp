#include <iostream>
#include <gtest/gtest.h>

int returnInt(const std::string &num)
{
    return stoi(num);
}

void returningInt()
{
    std::cout << "Good day" << std::endl;
}

int add(const int &num1, const int &num2)
{
    return num1 + num2;
}

int divide(const int &num1, const int &num2)
{

    return num1 / num2;
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

TEST(CheckReturnValue, returningInt)
{
    auto result = returnInt("1");
    returningInt();
    EXPECT_EQ(typeid(result), typeid(int));
    ASSERT_TRUE(typeid(result) == typeid(int));
    ASSERT_ANY_THROW(returnInt("a"));
}

TEST(MathOperations, addTest)
{
    int result = add(2, 2);
    ASSERT_EQ(result, 4);
}

TEST(MathOperations, divideTest)
{
    int num1 = 2, num2 = 2;
    ASSERT_NE(num2, 0);
    int result = divide(num1, num2);
    ASSERT_EQ(result, 1);
}

TEST(MathOperations, Nothing)
{
    ASSERT_DEATH(
        {
            int *p = nullptr;
            *p = 42;
        },
        ".*null pointer.*");

    EXPECT_DEATH({ int result = 1 / 0; },
                 ".*division by zero.*");
}
