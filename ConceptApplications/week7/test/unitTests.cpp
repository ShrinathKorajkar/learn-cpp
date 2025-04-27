#include <fstream>
#include <filesystem>
#include "company.hpp"

// TEST CASES FOR PRINT ERROR
class PrintErrorFixture : public ::testing::Test
{
public:
    std::ostringstream outputBuffer;
    std::stringstream input;
    std::streambuf *cinbuf;
    void SetUp() override
    {
        input << "123414584!@#$#%%^%*&(\n\n\n)";
        cinbuf = std::cin.rdbuf();
        std::cin.rdbuf(input.rdbuf());
    }

    void TearDown() override
    {
        std::cin.rdbuf(cinbuf);
    }
};

TEST_F(PrintErrorFixture, PrintError_Simple)
{
    printError("This is a Simple test message", outputBuffer);
    EXPECT_STREQ(outputBuffer.str().c_str(), "\nThis is a Simple test message\n");
}

TEST_F(PrintErrorFixture, PrintError_ClearStream)
{
    printError("This is a Simple test message", outputBuffer);
    ASSERT_FALSE(std::cin.fail());
    ASSERT_FALSE(std::cin.eof());
    ASSERT_TRUE(std::cin.good());
}

TEST_F(PrintErrorFixture, PrintError_NullPtr)
{
    printError(nullptr, outputBuffer);
    ASSERT_TRUE(outputBuffer.good());
}

TEST_F(PrintErrorFixture, PrintError_EmptyMessage)
{
    printError("", outputBuffer);
    ASSERT_TRUE(outputBuffer.good());
    EXPECT_STREQ(outputBuffer.str().c_str(), "\n\n");
}

TEST_F(PrintErrorFixture, PrintError_SpecialChars)
{
    printError("~!@@#$$%%^^&*()   SRFG1341 1345", outputBuffer);
    ASSERT_TRUE(outputBuffer.good());
    EXPECT_STREQ(outputBuffer.str().c_str(), "\n~!@@#$$%%^^&*()   SRFG1341 1345\n");
}

//
// TEST CASES FOR REPLACE CHARACTER
class CompanyFixture : public ::testing::Test
{
protected:
    Company *company;
    std::string directoryPath;

public:
    void
    SetUp() override
    {
        company = new Company();
        company->currentId = 101;
        directoryPath = company->getDirectoryPath();
        std::filesystem::remove_all(directoryPath);
    }
    void TearDown() override
    {
        std::filesystem::remove_all(directoryPath);
        delete company;
    }
};

class ReplaceCharSuite : public CompanyFixture
{
};

TEST_F(ReplaceCharSuite, ReplaceChar_Simple)
{
    std::string str = "Hello, world!";
    company->replaceChar(str, 'o', 'O');
    EXPECT_STREQ(str.c_str(), "HellO, wOrld!");
}

TEST_F(ReplaceCharSuite, ReplaceChar_EmptyStr)
{
    std::string str = "";
    company->replaceChar(str, 'a', 'b');
    EXPECT_EQ(str, "");
}

TEST_F(ReplaceCharSuite, ReplaceChar_NoReplacement)
{
    std::string str = "Hello, world!";
    company->replaceChar(str, 'x', 'y');
    EXPECT_EQ(str, "Hello, world!");
}

TEST_F(ReplaceCharSuite, ReplaceChar_NullCharacter)
{
    std::string str = "Hello, world!";
    company->replaceChar(str, 'o', '\0');
    EXPECT_STREQ(str.c_str(), "Hell\0, w\0rld!");
}

//
// TEST CASES FOR CALCULATE DURATION CLASS
class CalculateDurationSuite : public CompanyFixture
{
};

TEST_F(CalculateDurationSuite, CalculateDuration_PositiveDiff)
{
    time_t inTimestamp = 1609459200;
    time_t outTimestamp = 1609462861;
    struct tm result = company->calculateDuration(inTimestamp, outTimestamp);
    EXPECT_TRUE(result.tm_hour == 1);
    EXPECT_TRUE(result.tm_min == 1);
    EXPECT_TRUE(result.tm_sec == 1);
}

TEST_F(CalculateDurationSuite, CalculateDuration_NegativeDiff)
{
    time_t inTimestamp = 1609459261;
    time_t outTimestamp = 1609455600;
    struct tm result = company->calculateDuration(inTimestamp, outTimestamp);
    EXPECT_TRUE(result.tm_sec == -1);
    EXPECT_TRUE(result.tm_min == -1);
    EXPECT_TRUE(result.tm_hour == -1);
}

TEST_F(CalculateDurationSuite, CalculateDuration_ZeroDiff)
{
    time_t inTimestamp = 1609455600;
    time_t outTimestamp = 1609455600;
    struct tm result = company->calculateDuration(inTimestamp, outTimestamp);
    EXPECT_TRUE(result.tm_sec == 0);
    EXPECT_TRUE(result.tm_min == 0);
    EXPECT_TRUE(result.tm_hour == 0);
}

TEST_F(CalculateDurationSuite, CalculateDuration_LargeDiff)
{
    time_t inTimestamp = 1577836800;
    time_t outTimestamp = 1609459199;
    struct tm result = company->calculateDuration(inTimestamp, outTimestamp);
    EXPECT_TRUE(result.tm_sec == 59);
    EXPECT_TRUE(result.tm_min == 59);
    EXPECT_TRUE(result.tm_hour == 23);
    EXPECT_TRUE(result.tm_mday == 365);
}

//
// TEST FOR REGISTERING EMPLOYEE
class RegisterEmployeeSuite : public CompanyFixture
{
};

TEST_F(RegisterEmployeeSuite, RegistrationTest_Simple)
{
    std::string name = "John Doe";
    company->registerEmployee(name);
    std::string filePath = directoryPath + "101_John_Doe.txt";
    ASSERT_TRUE(std::filesystem::exists(filePath));
}

TEST_F(RegisterEmployeeSuite, RegistrationTest_NoName)
{
    std::string name = "";
    company->registerEmployee(name);
    std::string filePath = directoryPath + "101_.txt";
    ASSERT_TRUE(std::filesystem::exists(filePath));
}

TEST_F(RegisterEmployeeSuite, RegistrationTest_ComplexName)
{
    std::string name = "ThisIs A Complex Name !@@#$ 134% @#$^^&* aldfj 2345 _";
    company->registerEmployee(name);
    std::string filePath = directoryPath + "101_ThisIs_A_Complex_Name_!@@#$_134%_@#$^^&*_aldfj_2345__.txt";
    ASSERT_TRUE(std::filesystem::exists(filePath));
}

TEST_F(RegisterEmployeeSuite, RegistrationTest_WithoutDataDirectory)
{
    if (std::filesystem::exists(directoryPath))
    {
        std::filesystem::remove_all(directoryPath);
    }
    company->registerEmployee("Shri Ram");
    ASSERT_TRUE(std::filesystem::exists(directoryPath));
    std::string filePath = directoryPath + "101_Shri_Ram.txt";
    EXPECT_TRUE(std::filesystem::exists(filePath));
}

TEST_F(RegisterEmployeeSuite, RegistrationTest_MulitpleRegistration)
{
    company->registerEmployee("Shri");
    company->registerEmployee("Ram");
    company->registerEmployee("Setu");
    EXPECT_TRUE(std::filesystem::exists(directoryPath + "101_Shri.txt"));
    EXPECT_TRUE(std::filesystem::exists(directoryPath + "102_Ram.txt"));
    EXPECT_TRUE(std::filesystem::exists(directoryPath + "103_Setu.txt"));
}

TEST_F(RegisterEmployeeSuite, RegistrationTest_SameName)
{
    company->registerEmployee("Shri");
    company->registerEmployee("Shri");
    EXPECT_TRUE(std::filesystem::exists(directoryPath + "101_Shri.txt"));
    EXPECT_TRUE(std::filesystem::exists(directoryPath + "102_Shri.txt"));
}

//
// TEST FOR LIST ALL EMPLOYEES()
class MockForListEmployees : public Company
{
public:
    MOCK_METHOD(void, printAllEmployees, (), (override));
    MOCK_METHOD(void, printAllRecordsForEmployee, (), (override));
};

TEST(ListAllEmployeesSuite, ListAllEmployees_NoData)
{
    MockForListEmployees mock;
    std::filesystem::remove_all(mock.getDirectoryPath());
    EXPECT_CALL(mock, printAllEmployees()).Times(0);
    mock.listAllEmployees();
    ASSERT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock));
}

TEST(ListAllEmployeesSuite, ListAllEmployees_WithData)
{
    MockForListEmployees mock;
    std::filesystem::remove_all(mock.getDirectoryPath());
    EXPECT_CALL(mock, printAllEmployees()).Times(1);
    mock.registerEmployee("Shri");
    mock.listAllEmployees();
    EXPECT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock));
    std::filesystem::remove_all(mock.getDirectoryPath());
}

TEST(ListAllRecordsSuite, ListAllRecords_NoEmpData)
{
    MockForListEmployees mock;
    std::filesystem::remove_all(mock.getDirectoryPath());
    EXPECT_CALL(mock, printAllRecordsForEmployee()).Times(0);
    mock.listAllRecords();
    ASSERT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock));
}

TEST(ListAllRecordsSuite, ListAllRecords_WithEmpData)
{
    MockForListEmployees mock;
    EXPECT_CALL(mock, printAllRecordsForEmployee()).Times(1);
    mock.registerEmployee("Shri");
    mock.listAllRecords();
    EXPECT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock));
    std::filesystem::remove_all(mock.getDirectoryPath());
}

//
// TEST FOR PRINT ALL EMPLOYEES()
class MockForPrintingEmployees : public Company
{
public:
    MOCK_METHOD(void, replaceChar, (std::string & strToChange, const char &old, const char &replacement), (override));
    MOCK_METHOD(void, printEmployeeDetails, (std::stringstream & stream), (override));
    MOCK_METHOD(void, printPunchInPunchOutDetails, (std::ifstream & employeeFile), (override));
};

TEST(ListAllEmployeesSuite, PrintAllEmployees_NoData)
{
    MockForPrintingEmployees mock;
    std::filesystem::remove_all(mock.getDirectoryPath());
    EXPECT_CALL(mock, replaceChar(::testing::_, ::testing::_, ::testing::_)).Times(0);
    mock.listAllEmployees();
    ASSERT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock));
}

TEST(ListAllEmployeesSuite, PrintAllEmployees_WithData)
{
    MockForPrintingEmployees mock;
    std::filesystem::remove_all(mock.getDirectoryPath());
    EXPECT_CALL(mock, replaceChar(::testing::_, ::testing::_, ::testing::_)).Times(6);
    mock.registerEmployee("Shri");
    mock.registerEmployee("Ram");
    mock.registerEmployee("Sita");
    mock.listAllEmployees();
    EXPECT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock));
    std::filesystem::remove_all(mock.getDirectoryPath());
}

TEST(ListAllRecordsSuite, AllRecordEmp_NoEmpData)
{
    MockForPrintingEmployees mock;
    std::filesystem::remove_all(mock.getDirectoryPath());
    EXPECT_CALL(mock, printEmployeeDetails(::testing::_)).Times(0);
    EXPECT_CALL(mock, printPunchInPunchOutDetails(::testing::_)).Times(0);
    mock.listAllRecords();
    ASSERT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock));
}

TEST(ListAllRecordsSuite, AllRecordEmp_WithEmpData)
{
    MockForPrintingEmployees mock;
    std::filesystem::remove_all(mock.getDirectoryPath());
    EXPECT_CALL(mock, replaceChar(::testing::_, ::testing::_, ::testing::_)).Times(2);
    EXPECT_CALL(mock, printEmployeeDetails(::testing::_)).Times(2);
    EXPECT_CALL(mock, printPunchInPunchOutDetails(::testing::_)).Times(2);
    mock.registerEmployee("Shri");
    mock.registerEmployee("Ram");
    mock.listAllRecords();
    EXPECT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock));
    std::filesystem::remove_all(mock.getDirectoryPath());
}

//
// // TEST FOR PUNCH IN AND PUNCHOUT
class PunchInPunchOutSuite : public CompanyFixture
{
};

TEST_F(PunchInPunchOutSuite, PunchInForExistingEmp)
{
    company->registerEmployee("Shri");
    std::stringstream input("101\n");
    std::streambuf *oldcin = std::cin.rdbuf(input.rdbuf());
    company->punchInOut(1);
    std::cin.rdbuf(oldcin);
    std::string filePath = directoryPath + "101_Shri.txt";
    EXPECT_TRUE(std::filesystem::exists(filePath));
    EXPECT_TRUE(std::filesystem::file_size(filePath) > 0);
}

TEST_F(PunchInPunchOutSuite, PunchInForNonExistingEmp)
{
    company->registerEmployee("Shri");
    std::stringstream input("102\n");
    std::streambuf *oldcin = std::cin.rdbuf(input.rdbuf());
    company->punchInOut(1);
    std::cin.rdbuf(oldcin);
    std::string filePath = directoryPath + "101_Shri.txt";
    ASSERT_TRUE(std::filesystem::exists(filePath));
    EXPECT_TRUE(std::filesystem::file_size(filePath) == 0);
}

TEST_F(PunchInPunchOutSuite, PunchOutAfterPunchIn)
{
    company->registerEmployee("Shri");
    std::stringstream input("101\n101\n");
    std::streambuf *oldcin = std::cin.rdbuf(input.rdbuf());
    company->punchInOut(1);
    company->punchInOut(2);
    std::cin.rdbuf(oldcin);
    std::string filePath = directoryPath + "101_Shri.txt";
    ASSERT_TRUE(std::filesystem::exists(filePath));
    ASSERT_TRUE(std::filesystem::file_size(filePath) > 0);
    std::string line;
    int count = 0;
    std::ifstream file(filePath);
    while (getline(file, line))
    {
        count++;
    }
    EXPECT_EQ(count, 2);
}

TEST_F(PunchInPunchOutSuite, PunchOutBeforePunchIn)
{
    company->registerEmployee("Shri");
    std::stringstream input("101\n");
    std::streambuf *oldcin = std::cin.rdbuf(input.rdbuf());
    company->punchInOut(2);
    std::cin.rdbuf(oldcin);
    std::string filePath = directoryPath + "101_Shri.txt";
    ASSERT_TRUE(std::filesystem::exists(filePath));
    ASSERT_TRUE(std::filesystem::file_size(filePath) == 0);
}

TEST_F(PunchInPunchOutSuite, MulitplePuncInPunchOutSameEmp)
{
    company->registerEmployee("Shri");
    std::stringstream input("101\n101\n101\n101\n101\n101\n");
    std::streambuf *oldcin = std::cin.rdbuf(input.rdbuf());
    company->punchInOut(1);
    company->punchInOut(1);
    company->punchInOut(2);
    company->punchInOut(1);
    company->punchInOut(2);
    company->punchInOut(2);
    std::cin.rdbuf(oldcin);
    std::string filePath = directoryPath + "101_Shri.txt";
    ASSERT_TRUE(std::filesystem::exists(filePath));
    ASSERT_TRUE(std::filesystem::file_size(filePath) > 0);
    std::string line;
    int count = 0;
    std::ifstream file(filePath);
    while (getline(file, line))
    {
        count++;
    }
    EXPECT_EQ(count, 6);
}

TEST_F(PunchInPunchOutSuite, PunchOutForNonExistingEmp)
{
    company->registerEmployee("Shri");
    std::stringstream input("102\n");
    std::streambuf *oldcin = std::cin.rdbuf(input.rdbuf());
    company->punchInOut(2);
    std::cin.rdbuf(oldcin);
    std::string filePath = directoryPath + "101_Shri.txt";
    ASSERT_TRUE(std::filesystem::exists(filePath));
    EXPECT_TRUE(std::filesystem::file_size(filePath) == 0);
}

TEST_F(PunchInPunchOutSuite, MulitplePuncInPunchOutDiffEmp)
{
    company->registerEmployee("Shri");
    company->registerEmployee("Ram");
    std::stringstream input("101\n102\n101\n102\n101\n102\n101\n102\n101\n102\n101\n102\n");
    std::streambuf *oldcin = std::cin.rdbuf(input.rdbuf());
    company->punchInOut(1);
    company->punchInOut(1);
    company->punchInOut(1);
    company->punchInOut(1);
    company->punchInOut(2);
    company->punchInOut(2);
    company->punchInOut(1);
    company->punchInOut(1);
    company->punchInOut(2);
    company->punchInOut(2);
    company->punchInOut(2);
    company->punchInOut(2);
    std::cin.rdbuf(oldcin);
    std::string filePath = directoryPath + "101_Shri.txt";
    ASSERT_TRUE(std::filesystem::exists(filePath));
    ASSERT_TRUE(std::filesystem::file_size(filePath) > 0);
    std::string line;
    int count = 0;
    std::ifstream file(filePath);
    while (getline(file, line))
    {
        count++;
    }
    file.close();
    EXPECT_EQ(count, 6);
    filePath = directoryPath + "102_Ram.txt";
    ASSERT_TRUE(std::filesystem::exists(filePath));
    ASSERT_TRUE(std::filesystem::file_size(filePath) > 0);
    count = 0;
    file.open(filePath);
    while (getline(file, line))
    {
        count++;
    }
    file.close();
    EXPECT_EQ(count, 6);
}