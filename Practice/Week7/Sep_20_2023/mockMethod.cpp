#include <gtest/gtest.h>
#include <gmock/gmock.h>

class A
{
public:
    virtual int subtract(const int &a, const int &b)
    {
        return a - b;
    }
};

int add(const int &a, const int &b)
{
    return a + b;
}

class MockTest : public A
{
public:
    MOCK_METHOD(int, add, (const int &a, const int &b), ());
    // MOCK_METHOD(int, subtract, (const int &a, const int &b), (override));
};

TEST(AddTest, adding)
{
    MockTest test;
    EXPECT_CALL(test, add(1, 2)).WillOnce(::testing::Return(3));
    int result = test.add(1, 2);
    EXPECT_EQ(result, 3);
    result = test.subtract(2, 1);
    EXPECT_EQ(result, 1);
}