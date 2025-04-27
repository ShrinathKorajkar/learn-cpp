#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Calculator
{
public:
    virtual int Add(int a, int b) = 0;
    virtual int Subtract(int a, int b) = 0;
};

class MockCalculator : public Calculator
{
public:
    MOCK_METHOD(int, Add, (int a, int b), (override));
    MOCK_METHOD(int, Subtract, (int a, int b), (override));
};

TEST(CalculatorTest, Add)
{
    MockCalculator mockCalculator;
    EXPECT_CALL(mockCalculator, Add(2, 3)).WillOnce(::testing::Return(5));
    int result = mockCalculator.Add(2, 3);
    ASSERT_EQ(result, 5);
}

TEST(CalculatorTest, Subtract)
{
    MockCalculator mockCalculator;
    EXPECT_CALL(mockCalculator, Subtract(8, 3)).WillOnce(::testing::Return(5));
    int result = mockCalculator.Subtract(8, 3);
    ASSERT_EQ(result, 5);
}
