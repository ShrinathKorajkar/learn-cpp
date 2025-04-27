#ifndef EMPLOYEE_STORE_H
#define EMPLOYEE_STORE_H

#include "employeeData.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <list>

class EmployeeStore
{
private:
    static int employeeIdCounter;
    sql::mysql::MySQL_Driver *msqlDriver;
    sql::Connection *connection;
    sql::Statement *sqlStatement;
    sql::ResultSet *queryResult;

    EmployeeStore();
    void init();

public:
    ~EmployeeStore();

    static EmployeeStore &getInstance();

    bool saveEmployee(const EmployeeData &employeeData);
    int getNewEmployeeId();
    EmployeeData getEmployeeData(const int &employeeId);
    std::list<EmployeeData> getAllEmployeesData();
};

#endif // EMPLOYEE_STORE_H
