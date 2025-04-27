#ifndef COMPANY_H
#define COMPANY_H
#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

void printError(const char *message, std::ostream &outStream);
void printError(const char *message);
class Company
{
    static long currentId;
    static const std::string directoryPath;

    virtual void replaceChar(std::string &strToChange, const char &old, const char &replacement)
    {
        for (char &c : strToChange)
        {
            c = c == old ? replacement : c;
        }
    }

    virtual struct tm calculateDuration(const time_t &inTimestamp, const time_t &outTimestamp);
    virtual void printEmployeeDetails(std::stringstream &stream);
    virtual void printPunchInPunchOutDetails(std::ifstream &employeeFile);
    virtual void printAllRecordsForEmployee();
    virtual void printCompleteRecords(std::ifstream &employeeFile);
    virtual bool addPunchInOut(const int &empId, const int &choice);
    virtual void printAllEmployees();

public:
    static std::string getDirectoryPath()
    {
        return directoryPath;
    }

    void registerEmployee(const std::string &name);
    void listAllEmployees();
    void listAllRecords();
    void listSingleEmployeeRecord();
    void punchInOut(const int &choice);

    FRIEND_TEST(ReplaceCharSuite, ReplaceChar_Simple);
    FRIEND_TEST(ReplaceCharSuite, ReplaceChar_EmptyStr);
    FRIEND_TEST(ReplaceCharSuite, ReplaceChar_NoReplacement);
    FRIEND_TEST(ReplaceCharSuite, ReplaceChar_NullCharacter);
    FRIEND_TEST(CalculateDurationSuite, CalculateDuration_PositiveDiff);
    FRIEND_TEST(CalculateDurationSuite, CalculateDuration_NegativeDiff);
    FRIEND_TEST(CalculateDurationSuite, CalculateDuration_ZeroDiff);
    FRIEND_TEST(CalculateDurationSuite, CalculateDuration_LargeDiff);

    friend class CompanyFixture;
};

#endif // !COMPANY_H