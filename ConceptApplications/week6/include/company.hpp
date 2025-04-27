#ifndef COMPANY_H
#define COMPANY_H
#include <iostream>

void printError(const char *message);

class Company
{
    static long currentId;
    static const std::string directoryPath;

    void replaceChar(std::string &strToChange, const char &old, const char &replacement)
    {
        for (char &c : strToChange)
        {
            c = c == old ? replacement : c;
        }
    }

    void printAllEmployees();
    void printEmployeeDetails(std::stringstream &stream);
    struct tm calculateDuration(const time_t &inTimestamp, const time_t &outTimestamp);
    void printPunchInPunchOutDetails(std::ifstream &employeeFile);
    void printAllRecordsForEmployee();
    void printCompleteRecords(std::ifstream &employeeFile);
    bool addPunchInOut(const int &empId, const int &choice);

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
};

#endif // !COMPANY_H