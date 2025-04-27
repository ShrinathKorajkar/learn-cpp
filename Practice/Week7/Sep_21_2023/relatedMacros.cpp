#include <gtest/gtest.h>
#include <gmock/gmock.h>

class TestMacros
{
public:
    virtual ~TestMacros() {}
    virtual int returnInt()
    {
        return 2;
    }
    virtual int noReturn(int a)
    {
        return a;
    }
};

class MockTestMacros
{
public:
    MOCK_METHOD0(returnInt, int());
    MOCK_METHOD1(noReturn, int(int a));
};

TEST(macrosTest, test1)
{
    MockTestMacros testObj;
    int a;
    EXPECT_CALL(testObj, returnInt()).Times(2).WillRepeatedly(::testing::Return(2));
    EXPECT_CALL(testObj, noReturn(::testing::_)).Times(1).WillOnce(::testing::ReturnArg<0>());
    a = testObj.returnInt();
    a = testObj.returnInt();
    ASSERT_EQ(a, 2);

    a = testObj.noReturn(3);
    ASSERT_EQ(a, 3);
}