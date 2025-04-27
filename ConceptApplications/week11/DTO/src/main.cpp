#include "employeeMgmt.h"
#include <iostream>
#include <limits>

void createEmployee(EmployeeManager &manager)
{
    try
    {
        manager.createEmployee();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "SQL Exception: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error : " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown exception occurred" << std::endl;
    }
}

void displayEmployeeData(EmployeeManager &manager)
{
    try
    {
        manager.displayEmployee();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "SQL Exception: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown exception occurred" << std::endl;
    }
}

void displayAllEmployeesData(EmployeeManager &manager)
{
    try
    {
        manager.displayAllEmployees();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "SQL Exception: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown exception occurred" << std::endl;
    }
}

int main()
{
    EmployeeStore &employeeStore = EmployeeStore::getInstance();
    EmployeeManager manager(employeeStore);

    int choice = 0;
    while (true)
    {
        std::cout << "\n\n1.Create Employee     2.Display Employee Info    3.Display All Employees Info     4.Exit";
        std::cout << "\nEnter Your Choice : ";
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice)
        {
        case 1:
            createEmployee(manager);
            break;
        case 2:
            displayEmployeeData(manager);
            break;
        case 3:
            displayAllEmployeesData(manager);
            break;
        case 4:
            break;
        default:
            std::cout << "Invalid Choice" << std::endl;
        }

        if (choice == 4)
        {
            break;
        }
    }
    return 0;
}
