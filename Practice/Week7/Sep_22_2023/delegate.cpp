#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Calculator
{
public:
    virtual ~Calculator() {}
    virtual int Add(int a, int b) = 0;
};

class MockCalculator : public Calculator
{
public:
    MOCK_METHOD(int, Add, (int a, int b), (override));
};

class MockCalculatorDelegate : public Calculator
{
public:
    MOCK_METHOD(int, Add, (int a, int b), (override));
};

TEST(CalculatorTest, DelegateExample)
{
    MockCalculator mockCalculator;
    MockCalculatorDelegate mockDelegate;

    ON_CALL(mockCalculator, Add(testing::_, testing::_))
        .WillByDefault(testing::Invoke(&mockDelegate, &MockCalculatorDelegate::Add));

    EXPECT_CALL(mockDelegate, Add(2, 3))
        .WillOnce(testing::Return(10));

    int result = mockCalculator.Add(2, 3);
    ASSERT_EQ(result, 10);
}
