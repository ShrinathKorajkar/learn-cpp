#ifndef EMPLOYEE_DATA_H
#define EMPLOYEE_DATA_H

#include <string>

class EmployeeData
{
private:
    int id;
    std::string name;
    int age;

public:
    EmployeeData(const int &id, const std::string &name, const int &age)
        : id(id), name(name), age(age) {}

    int getId() const
    {
        return this->id;
    }

    std::string getName() const
    {
        return this->name;
    }

    int getAge() const
    {
        return this->age;
    }
};

#endif // EMPLOYEE_DATA_H