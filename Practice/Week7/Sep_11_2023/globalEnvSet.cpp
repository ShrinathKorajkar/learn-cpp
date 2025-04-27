#include <gtest/gtest.h>
#include <iostream>
/*
    executes before any other test case and tear down happens after all tests cases
*/
class DatabaseConnection
{
public:
    DatabaseConnection()
    {
        std::cout << "Connecting to the database..." << std::endl;
    }

    ~DatabaseConnection()
    {
        std::cout << "Closing the database connection." << std::endl;
    }
};

class MyEnvironment : public ::testing::Environment
{
private:
    static DatabaseConnection *databaseConnection;

public:
    void SetUp() override
    {
        databaseConnection = new DatabaseConnection();
    }

    void TearDown() override
    {
        delete databaseConnection;
        databaseConnection = nullptr;
    }

    static DatabaseConnection *GetDatabaseConnection()
    {
        return databaseConnection;
    }
};

DatabaseConnection *MyEnvironment::databaseConnection = nullptr;

TEST(DatabaseTest, Test1)
{
    DatabaseConnection *dbConnection = MyEnvironment::GetDatabaseConnection();
    ASSERT_TRUE(dbConnection != nullptr);
}

TEST(DatabaseTest, Test2)
{
    DatabaseConnection *dbConnection = MyEnvironment::GetDatabaseConnection();
    ASSERT_TRUE(dbConnection != nullptr);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new MyEnvironment);
    return RUN_ALL_TESTS();
}
