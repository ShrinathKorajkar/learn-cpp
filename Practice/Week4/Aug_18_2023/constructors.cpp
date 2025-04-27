#include <iostream>

class myClass
{
private:
    std::string name;
    int age;

public:
    myClass() : name(""), age(0) {}

    myClass(const std::string &newName, int newAge) : name(newName), age(newAge) {}

    myClass(const myClass &other) : name(other.name), age(other.age) {} // copy

    myClass(const std::string &newName) : myClass(newName, 0) {} // delegating constructor

    void printInfo()
    {
        std::cout << name << " : " << age << std::endl;
    }
};

int main()
{
    myClass person;
    myClass person2("Shri");
    myClass person3("Shri", 21);
    myClass person5 = myClass("shri", 21);
    myClass person4(person3);
    myClass person6 = person5;

    person.printInfo();
    person2.printInfo();
    person3.printInfo();
    person4.printInfo();

    void *memory = operator new(sizeof(myClass));
    myClass *obj = new (memory) myClass("shri", 22);
    obj->printInfo();

    obj->~myClass();
    operator delete(memory);
    return 0;
}