#ifndef EMPLOYEE_MANAGER_H
#define EMPLOYEE_MANAGER_H

#include "employeeData.h"
#include "employeeStore.h"

class EmployeeManager
{
private:
    EmployeeStore &employeeStore;

public:
    EmployeeManager(EmployeeStore &employeeStore);

    void createEmployee();
    void displayEmployee();
    void displayAllEmployees();
};

#endif // EMPLOYEE_MANAGER_H
