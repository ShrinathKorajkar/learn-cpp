#include <string>

/*
 * Q: Is 'employee' an object or a data structure ? Why ?
 * Ans: It is a data structure, as there is no buisness logic present in the
 *      class and only data with its accessors methods are given.
 */

class Employee
{

    std::string name;
    int age;
    float salary;

public:
    std::string getName();
    int getAge();
    float getSalary();

    void setName(std::string name);
    void setAge(int age);
    void setSalary(float salary);
};

Employee employee;
