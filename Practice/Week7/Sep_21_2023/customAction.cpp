#include <gtest/gtest.h>
#include <gmock/gmock.h>

class CustomReturnAction
{
public:
    CustomReturnAction(int value) : value_(value) {}

    int operator()() const
    {
        return value_;
    }

private:
    int value_;
};

class MockCalculator
{
public:
    MOCK_METHOD(int, Add, (int a, int b), ());
};

TEST(CalculatorTest, CustomActionExample)
{
    MockCalculator mockCalculator;

    EXPECT_CALL(mockCalculator, Add(2, 3)).WillOnce(CustomReturnAction(5));

    int result = mockCalculator.Add(2, 3);
    ASSERT_EQ(result, 5);
}
