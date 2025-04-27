#include <iostream>
#include <filesystem>
#include "company.hpp"

void adminFunctions(const int &choice, Company &company)
{
    std::string name;

    switch (choice)
    {
    case 1:
        std::cin.ignore();
        std::cout << "\nEnter Employee Name : ";
        std::getline(std::cin, name);
        company.registerEmployee(name);
        break;
    case 2:
        company.listAllEmployees();
        break;
    case 3:
        company.listAllRecords();
        break;
    case 4:
        company.listSingleEmployeeRecord();
        break;
    case 5:
        break;
    default:
        printError("Invalid Choice... Please try again");
    }
}

void admin(Company &company)
{
    std::string passwd;
    std::cout << "\nEnter Admin Password: ";
    std::cin >> passwd;
    if (passwd.compare("admin") != 0)
    {
        std::cout << "Wrong Admin Password" << std::endl;
        return;
    }

    int choice = 0;
    do
    {
        std::cout << "\nEnter Your Choice : " << std::endl;
        std::cout << "1. Register Employee      2. List All Employees      3. List All Records" << std::endl;
        std::cout << "4. List Single Record      5. Return" << std::endl;
        std::cin >> choice;
        if (std::cin.fail())
        {
            printError("Invalid Choice... Please try again");
            continue;
        }
        adminFunctions(choice, company);
    } while (choice != 5);
}

void startSystem(const int &choice)
{

    Company ITT;
    switch (choice)
    {
        {
        case 1:
        case 2:

            ITT.punchInOut(choice);
            break;
        case 3:
            admin(ITT);
            break;
        case 4:
            break;
        default:
            printError("Invalid Choice.. Please try again");
        }
    }
}

void destroyResources()
{
    if (std::filesystem::exists(Company::getDirectoryPath()))
    {
        std::filesystem::remove_all(Company::getDirectoryPath());
    }
}

int main()
{
    int choice = 0;
    do
    {
        std::cout << "\nEnter Your Choice : " << std::endl;
        std::cout << "1. Punch-In     2. Punch-Out     3. Admin     4. Exit" << std::endl;
        std::cin >> choice;
        if (std::cin.fail())
        {
            printError("Invalid Choice... Please Try Again.");
            continue;
        }
        startSystem(choice);
    } while (choice != 4);

    destroyResources();

    return 0;
}
