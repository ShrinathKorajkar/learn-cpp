#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>

class TryMatcher
{
public:
    virtual ~TryMatcher() {}
    virtual void greet(int a) = 0;
};

class MockTryMatcher : public TryMatcher
{
public:
    MOCK_METHOD1(greet, void(int a));
};

TEST(MockTryMatcher, test)
{
    MockTryMatcher myObj;
    EXPECT_CALL(myObj, greet(::testing::_)).WillOnce([](int a)
                                                     { std::cout << "hello1" << std::endl; });
    EXPECT_CALL(myObj, greet(::testing::Eq(20))).WillOnce([](int a)
                                                          { std::cout << "hello2" << std::endl; });
    EXPECT_CALL(myObj, greet(::testing::AllOf(::testing::Gt(20), ::testing::Lt(30)))).WillOnce([](int a)
                                                                                               { std::cout << "hello3" << std::endl; });
    myObj.greet(10);
    myObj.greet(20);
    myObj.greet(25);
}