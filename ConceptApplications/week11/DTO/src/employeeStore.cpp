#include "employeeStore.h"
#include <iostream>

int EmployeeStore::employeeIdCounter = 0;

EmployeeStore::EmployeeStore() : msqlDriver(nullptr), connection(nullptr), sqlStatement(nullptr), queryResult(nullptr)
{
    msqlDriver = sql::mysql::get_mysql_driver_instance();
    connection = msqlDriver->connect("tcp://127.0.0.1:3306/company", "shrinathkkorajkar", "sharky@123");
    sqlStatement = connection->createStatement();

    init();
}

EmployeeStore::~EmployeeStore()
{
    delete queryResult;
    delete sqlStatement;
    delete connection;
}

EmployeeStore &EmployeeStore::getInstance()
{
    static EmployeeStore storeInstance;
    return storeInstance;
}

void EmployeeStore::init()
{
    std::string query = "CREATE TABLE IF NOT EXISTS employee \
                         (id INT PRIMARY KEY, \
                         name VARCHAR(25) NOT NULL, \
                         age INT NOT NULL \
                         )";
    sqlStatement->execute(query);

    sql::ResultSet *resultSet = sqlStatement->executeQuery("SELECT MAX(id) FROM employee");
    if (resultSet->next())
    {
        employeeIdCounter = resultSet->getInt(1);
    }
}

int EmployeeStore::getNewEmployeeId()
{
    return ++employeeIdCounter;
}

bool EmployeeStore::saveEmployee(const EmployeeData &employeeData)
{
    int employeeId = employeeData.getId();
    std::string employeeName = employeeData.getName();
    int employeeAge = employeeData.getAge();

    std::string query = "INSERT INTO employee (id, name, age) VALUES (" +
                        std::to_string(employeeId) + ", '" + employeeName +
                        "', " + std::to_string(employeeAge) + ")";

    bool status = sqlStatement->execute(query);
    return status;
}

EmployeeData EmployeeStore::getEmployeeData(const int &employeeId)
{
    std::string query = "SELECT name, age FROM employee WHERE id=" + std::to_string(employeeId);
    queryResult = sqlStatement->executeQuery(query);
    queryResult->next();

    int employeeAge = queryResult->getInt("age");
    std::string employeeName = queryResult->getString("name");
    return EmployeeData(employeeId, employeeName, employeeAge);
}

std::list<EmployeeData> EmployeeStore::getAllEmployeesData()
{
    std::string query = "SELECT * FROM employee";
    queryResult = sqlStatement->executeQuery(query);

    std::list<EmployeeData> allEmployees;
    while (queryResult->next())
    {
        int employeeId = queryResult->getInt("id");
        std::string employeeName = queryResult->getString("name");
        int employeeAge = queryResult->getInt("age");

        allEmployees.emplace_back(EmployeeData{employeeId, employeeName, employeeAge});
    }

    return allEmployees;
}
