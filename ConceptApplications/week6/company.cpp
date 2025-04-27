#include <fstream>
#include <ctime>
#include <sstream>
#include <filesystem>
#include <iomanip>
#include <sys/stat.h>
#include "company.hpp"
#define PUNCH_IN 1
#define PUNCH_OUT 2

namespace fs = std::filesystem;

long Company::currentId = 101;
const std::string Company::directoryPath = "./data/";

void printError(const char *message)
{
    std::cout << "\n"
              << message << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

struct tm Company::calculateDuration(const time_t &inTimestamp, const time_t &outTimestamp)
{
    struct tm diffTime;
    long duration = difftime(outTimestamp, inTimestamp);
    diffTime.tm_sec = duration % 60;
    diffTime.tm_min = (duration / 60) % 60;
    diffTime.tm_hour = duration / 3600;
    return diffTime;
}

void Company::printEmployeeDetails(std::stringstream &stream)
{
    int empId = 0;
    std::string empName;
    stream >> empId >> empName;

    replaceChar(empName, '_', ' ');
    empName = empName.substr(1);

    std::cout << std::setw(15) << empId << std::left << std::setw(20) << empName;
}

void Company::printPunchInPunchOutDetails(std::ifstream &employeeFile)
{
    time_t inTimestamp, outTimestamp = 0, timestamp;
    char inbuf[25] = "---";
    char outbuf[25] = "---";
    char durationBuf[15] = "---";
    int action;

    if (employeeFile >> action >> inTimestamp)
    {
        strftime(inbuf, sizeof(inbuf), "%H:%M:%S", localtime(&inTimestamp));
    }

    while (employeeFile >> action >> timestamp)
    {
        if (action == PUNCH_OUT)
        {
            outTimestamp = timestamp;
        }
    }

    if (outTimestamp != 0)
    {
        strftime(outbuf, sizeof(outbuf), "%H:%M:%S", localtime(&outTimestamp));
        struct tm diffTime = calculateDuration(inTimestamp, outTimestamp);
        strftime(durationBuf, sizeof(durationBuf), "%H:%M:%S", &diffTime);
    }

    std::cout << std::left << std::setw(20) << inbuf << std::left << std::setw(20) << outbuf << durationBuf << std::endl;
}

void Company::printAllRecordsForEmployee()
{
    for (const auto &file : fs::directory_iterator(directoryPath))
    {
        std::string fileName = file.path().stem().string();
        std::stringstream stream(fileName);

        printEmployeeDetails(stream);

        std::ifstream employeeFile(file.path());
        printPunchInPunchOutDetails(employeeFile);
        employeeFile.close();
    }
}

void Company::printCompleteRecords(std::ifstream &employeeFile)
{

    std::cout << std::left << std::setw(12) << "Action" << std::setw(13) << "Date"
              << "Time" << std::endl;
    time_t timestamp;
    int action;
    while (employeeFile >> action >> timestamp)
    {
        char buf[25];
        std::string actionStr;
        actionStr = action == PUNCH_IN ? "Punch-In" : "Punch-Out";
        strftime(buf, sizeof(buf), "%d-%m-%Y   %H:%M:%S", localtime(&timestamp));
        std::cout << std::left << std::setw(12) << actionStr << std::setw(12) << buf << std::endl;
    }
    std::cout << std::endl;
    employeeFile.close();
}

bool Company::addPunchInOut(const int &empId, const int &choice)
{
    bool foundEmployee = false;

    for (const auto &file : fs::directory_iterator(directoryPath))
    {
        std::string fileName = file.path().filename().string();
        std::stringstream stream(fileName);

        int searchId = 0;
        stream >> searchId;

        if (empId == searchId)
        {
            foundEmployee = true;
            struct stat fileStat;
            stat(file.path().c_str(), &fileStat);
            if (choice == 2 && fileStat.st_size == 0)
            {
                std::cout << "\nNeed to Punch-In before Punch-Out\n\n";
            }
            else
            {
                std::ofstream employeeFile(file.path(), std::ios::app);
                time_t currentTime = time(nullptr);
                employeeFile << choice << " " << currentTime << std::endl;
                std::cout << "\nPunch Successfull" << std::endl;
                employeeFile.close();
            }
            break;
        }
    }
    return foundEmployee;
}

void Company::registerEmployee(const std::string &name)
{
    if (!fs::exists(directoryPath))
    {
        fs::create_directory(directoryPath);
    }

    std::string filePath;
    filePath.append(directoryPath + std::to_string(currentId) + " " + name + ".txt");
    currentId++;

    replaceChar(filePath, ' ', '_');
    std::ofstream file(filePath);

    file.close();
    std::cout << "\nRegistration Successfull... New Employee Id : " << currentId - 1 << std::endl;
}

void Company::printAllEmployees()
{
    for (const auto &file : fs::directory_iterator(directoryPath))
    {
        if (fs::is_regular_file(file))
        {
            std::string fileName = file.path().stem().string();

            replaceChar(fileName, '_', ' ');

            std::stringstream stream(fileName);

            int empId = 0;
            std::string name;

            stream >> empId >> name;
            std::cout << std::setw(15) << empId << name << std::endl;
        }
    }
}

void Company::listAllEmployees()
{
    if (!fs::exists(directoryPath))
    {
        std::cerr << "\nNo Data Available!\n\n";
        return;
    }
    std::cout << "\n******* List Of ALL Employees *******" << std::endl;
    std::cout << std::left << std::setw(15) << "Employee Id"
              << "Employee Name" << std::endl;

    printAllEmployees();
    std::cout << std::endl;
}

void Company::listAllRecords()
{
    if (!fs::exists(directoryPath))
    {
        std::cout << "\nNo Employees Registered Yet!\n\n";
        return;
    }

    std::cout << "\n***** Employee Record *****" << std::endl;
    std::cout << std::left << std::setw(15) << "Employee Id"
              << std::setw(20) << "Name"
              << std::setw(20) << "Punch-In"
              << std::setw(20) << "Punch-Out"
              << "Duration" << std::endl;

    printAllRecordsForEmployee();

    std::cout << std::endl;
}

void Company::listSingleEmployeeRecord()
{
    if (!fs::exists(directoryPath))
    {
        std::cout << "\nNo Employees Registered Yet!\n"
                  << std::endl;
        return;
    }

    int searchId = 0;
    std::cout << "\nEnter Employee Id : ";
    std::cin >> searchId;
    if (std::cin.fail())
    {
        printError("Invalid Input : Please Enter Integers");
        return;
    }
    bool foundEmployee = false;

    std::cout << "\n***** Employee Record *****" << std::endl;
    for (const auto &file : fs::directory_iterator(directoryPath))
    {
        std::string fileName = file.path().stem().string();
        std::stringstream stream(fileName);

        int empId = 0;
        std::string empName;
        stream >> empId >> empName;

        if (empId == searchId)
        {
            foundEmployee = true;
            replaceChar(empName, '_', ' ');
            empName = empName.substr(1);
            std::cout << "Id : " << empId << "     Name : " << empName << std::endl;

            struct stat fileStat;
            stat(file.path().c_str(), &fileStat);
            if (fileStat.st_size == 0)
            {
                std::cout << "\nNo Punch-In and Punch-Out Records\n\n";
            }
            else
            {
                std::ifstream employeeFile(file.path());
                printCompleteRecords(employeeFile);
                employeeFile.close();
            }

            break;
        }
    }
    if (!foundEmployee)
    {
        std::cout << "\nEmployee Record Not Found...\n"
                  << std::endl;
    }
}

void Company::punchInOut(const int &choice)
{
    if (!fs::exists(directoryPath))
    {
        std::cout << "\nNo Employees Available!... Register Employees First\n"
                  << std::endl;
        return;
    }
    int empId = 0;
    std::cout << "\nEnter Employee Id : ";
    std::cin >> empId;
    if (std::cin.fail())
    {
        printError("Invalid Input : Please Enter Correct Employee Id");
        return;
    }

    bool foundEmployee = addPunchInOut(empId, choice);

    if (!foundEmployee)
    {
        std::cout << "\nEntered Employee Id Not Found... Please Enter Correct ID\n"
                  << std::endl;
    }
}
