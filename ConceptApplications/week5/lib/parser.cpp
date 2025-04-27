#include <iomanip>
#include "parser.hpp"

void Employee::setData(const int &id, const std::string &name, const int &age, const int &joiningYear)
{
    this->empId = id;
    this->name = name;
    this->age = age;
    this->joiningYear = joiningYear;
}

std::ostream &operator<<(std::ostream &outputStream, const Employee &employee)
{
    outputStream << employee.empId << " : "
                 << std::left << std::setw(15) << employee.name
                 << " Joined in : " << employee.joiningYear;
    return outputStream;
}

void CsvParser::parseFile()
{
    Employee E;
    {
        std::cout << "\n********** EMPLOYEES DETAILS **********" << std::endl;

        in.read_header(io::ignore_extra_column, "EMPID", "NAME", "AGE", "YEAR_OF_JOINING");
        while (in.read_row(employeeId, name, age, yearOfJoining))
        {
            E.setData(employeeId, name, age, yearOfJoining);
            std::cout << E << std::endl;
        }
    }
}

void JsonParser::parseFile()
{
    Employee E;
    reader.parse(file, root);

    std::cout << "\n********** EMPLOYEES DETAILS **********" << std::endl;

    for (const auto &entry : root)
    {
        const int empId = entry["EMPID"].asInt();
        const std::string name = entry["NAME"].asString();
        const int age = entry["AGE"].asInt();
        const int dateOfJoining = entry["YEAR_OF_JOINING"].asInt();
        E.setData(empId, name, age, dateOfJoining);
        std::cout << E << std::endl;
    }
}

void XmlParser::parseFile()
{
    Employee E;
    std::cout << "\n********** EMPLOYEES DETAILS **********" << std::endl;

    pugi::xml_node employees = doc.child("data");
    for (pugi::xml_node employee : employees.children("employee"))
    {
        int empId = atoi(employee.child_value("EMPID"));
        std::string name = employee.child_value("NAME");
        int age = atoi(employee.child_value("AGE"));
        int dateOfJoining = atoi(employee.child_value("YEAR_OF_JOINING"));
        E.setData(empId, name, age, dateOfJoining);
        std::cout << E << std::endl;
    }
}
