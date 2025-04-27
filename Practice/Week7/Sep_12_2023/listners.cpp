#include <iostream>
#include <gtest/gtest.h>

class MyTestEventListener : public testing::TestEventListener
{
public:
    void OnTestStart(const testing::TestInfo &test_info) override
    {
        std::cout << "Test case " << test_info.name() << " is starting." << std::endl;
    }

    void OnTestEnd(const testing::TestInfo &test_info) override
    {
        std::cout << "Test case " << test_info.name() << " has finished." << std::endl;
    }

    void OnTestProgramStart(const testing::UnitTest &unit_test) override {}
    void OnTestIterationStart(const testing::UnitTest &unit_test, int iteration) override {}
    void OnEnvironmentsSetUpStart(const testing::UnitTest &unit_test) override {}
    void OnEnvironmentsSetUpEnd(const testing::UnitTest &unit_test) override {}
    void OnTestPartResult(const testing::TestPartResult &result) override {}
    void OnEnvironmentsTearDownStart(const testing::UnitTest &unit_test) override {}
    void OnEnvironmentsTearDownEnd(const testing::UnitTest &unit_test) override {}
    void OnTestIterationEnd(const testing::UnitTest &unit_test, int iteration) override {}
    void OnTestProgramEnd(const testing::UnitTest &unit_test) override {}
};

class MyAssertionEventListener : public testing::TestEventListener
{
public:
    void OnTestPartResult(const testing::TestPartResult &result) override
    {
        if (result.failed())
        {
            std::cerr << "Assertion failed in test case " << result.file_name() << ":" << result.line_number() << std::endl;
        }
    }
    void OnTestStart(const testing::TestInfo &test_info) override {}
    void OnTestEnd(const testing::TestInfo &test_info) override {}
    void OnTestProgramStart(const testing::UnitTest &unit_test) override {}
    void OnTestIterationStart(const testing::UnitTest &unit_test, int iteration) override {}
    void OnEnvironmentsSetUpStart(const testing::UnitTest &unit_test) override {}
    void OnEnvironmentsSetUpEnd(const testing::UnitTest &unit_test) override {}
    void OnEnvironmentsTearDownStart(const testing::UnitTest &unit_test) override {}
    void OnEnvironmentsTearDownEnd(const testing::UnitTest &unit_test) override {}
    void OnTestIterationEnd(const testing::UnitTest &unit_test, int iteration) override {}
    void OnTestProgramEnd(const testing::UnitTest &unit_test) override {}
};

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    ::testing::UnitTest::GetInstance()->listeners().Append(new MyTestEventListener);
    ::testing::UnitTest::GetInstance()->listeners().Append(new MyAssertionEventListener);

    return RUN_ALL_TESTS();
}

TEST(MyTestSuite, Test1)
{
    ASSERT_TRUE(true);
}

TEST(MyTestSuite, Test2)
{
}
