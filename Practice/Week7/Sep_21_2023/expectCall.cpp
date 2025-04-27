#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Calculator
{
public:
    virtual ~Calculator() {}
    virtual int add(int a, int b) const = 0;
};

class MathOperation
{
    Calculator *calculator;

public:
    MathOperation(Calculator *calculator) : calculator(calculator) {}
    int doubleAdd(int a, int b)
    {
        return calculator->add(a, b) * 2;
    }
};

class MockCalculator : public Calculator
{
public:
    MOCK_CONST_METHOD2(add, int(int a, int b));
};

TEST(MathOperationTest, DoubleAdd)
{
    MockCalculator calculator;
    MathOperation operation(&calculator);

    EXPECT_CALL(calculator, add(3, 4)).Times(1).WillOnce(::testing::Return(7));
    int result = operation.doubleAdd(3, 4);
    ASSERT_EQ(result, 14);
    EXPECT_TRUE(::testing::Mock::VerifyAndClearExpectations(&calculator));
}