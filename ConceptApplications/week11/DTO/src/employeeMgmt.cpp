#include "employeeMgmt.h"
#include <iostream>
#include <iomanip>

EmployeeManager::EmployeeManager(EmployeeStore &employeeStore) : employeeStore(employeeStore) {}

void EmployeeManager::createEmployee()
{
    int employeeId;
    std::string employeeName;
    int employeeAge;

    std::cout << "\nEnter the details of Employee : " << std::endl;
    std::cout << "Employee Name : ";
    std::cin.ignore();
    std::getline(std::cin, employeeName);
    std::cout << "Employee Age  : ";
    std::cin >> employeeAge;
    employeeId = employeeStore.getNewEmployeeId();

    EmployeeData employeeData(employeeId, employeeName, employeeAge);
    employeeStore.saveEmployee(employeeData);

    std::cout << "Success!... Employe with ID : " + std::to_string(employeeId) + " Created" << std::endl;
}

void EmployeeManager::displayEmployee()
{
    int employeeId;
    std::cout << "\nEnter Employee ID to view Details: ";
    std::cin >> employeeId;

    EmployeeData employee = employeeStore.getEmployeeData(employeeId);

    std::cout << "Employee Name : " << employee.getName() << std::endl;
    std::cout << "Employee Age  : " << employee.getAge() << std::endl;
}

void EmployeeManager::displayAllEmployees()
{
    int serialNo = 1;
    std::cout << "\nAll Employees Details" << std::endl;
    std::cout << std::left << std::setw(10) << "S.No" << std::left << std::setw(15) << "Name"
              << "Age" << std::endl;
    std::list<EmployeeData> allEmployees = employeeStore.getAllEmployeesData();
    for (auto employee : allEmployees)
    {
        std::cout << std::setw(10) << serialNo++;
        std::cout << std::left << std::setw(15) << employee.getName();
        std::cout << employee.getAge() << std::endl;
    }
}
