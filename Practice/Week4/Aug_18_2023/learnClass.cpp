#include <iostream>

class myClass
{
private:
    std::string name;
    int age;

public:
    void setName(std::string newName)
    {
        name = newName;
    }

    void setAge(int newAge)
    {
        age = newAge;
    }

    std::string getName()
    {
        return name;
    }

    int getAge()
    {
        return age;
    }
};

int main()
{
    myClass person;
    person.setName("John Cena");
    person.setAge(21);

    std::cout << "Name : " << person.getName() << std::endl;
    std::cout << "Age : " << person.getAge() << std::endl;

    return 0;
}