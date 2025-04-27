#include <string>
class Employee
{
    int id;
    std::string name;
    std::string department;
    bool working;

public:
    void saveEmployeeTODatabase();
    void printEmployeeDetailReportXML();
    void printEmployeeDetailReportCSV();
    void terminateEmployee();
    bool isWorking();
};
