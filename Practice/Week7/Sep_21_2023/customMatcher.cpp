#include <gmock/gmock.h>

MATCHER_P(ContainsSubstring, substring, "")
{
    return arg.find(substring) != std::string::npos;
}

class MockDatabase
{
public:
    MOCK_METHOD1(Search, bool(const std::string &query));
};

TEST(DatabaseTest, CustomMatcherExample)
{
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, Search(ContainsSubstring("GMock")))
        .Times(1)
        .WillOnce(::testing::Return(true));

    bool result = mockDb.Search("Testing GMock Library");
    ASSERT_TRUE(result);
}
