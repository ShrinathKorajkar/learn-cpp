#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Calculator
{
public:
    virtual ~Calculator() {}
    virtual double Divide(double a, double b) = 0;
};

class MockCalculator : public Calculator
{
public:
    MOCK_METHOD(double, Divide, (double a, double b), (override));
};

TEST(CalculatorTest, DivideByZero)
{
    MockCalculator mock;

    ON_CALL(mock, Divide(testing::_, 0.0)).WillByDefault(testing::Return(0.0));

    EXPECT_DOUBLE_EQ(mock.Divide(10.0, 0.0), 0.0);
}

TEST(CalculatorTest, NormalDivision)
{
    MockCalculator mock;

    ON_CALL(mock, Divide(testing::_, testing::DoubleEq(2.0))).WillByDefault(testing::Return(5.0));

    EXPECT_DOUBLE_EQ(mock.Divide(10.0, 2.0), 5.0);
    EXPECT_DOUBLE_EQ(mock.Divide(20.0, 2.0), 5.0);
}

TEST(CalculatorTest, RandomDivision)
{
    MockCalculator mock;
    ON_CALL(mock, Divide(::testing::_, ::testing::_)).WillByDefault([](int x, int y)
                                                                    { return x / y; });
    EXPECT_DOUBLE_EQ(mock.Divide(20.0, 4.0), 5.0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
