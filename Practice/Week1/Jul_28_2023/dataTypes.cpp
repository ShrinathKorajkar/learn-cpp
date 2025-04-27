/*
    1. Primitive Data Types :- char, int, float, double, bool
    2. User-Defined :- array, pointers, references, typedef, structure, classes, enum, union

*/

#include <iostream>
#include <string>
using namespace std;

struct Person
{
    string name;
    int age;
};

struct MyStruct
{
    char c;
    int x;
    double d;
} __attribute__((packed));

struct alignas(8) MyStruct2
{
    int x;
    char c;
};

typedef int number;

void changeVar(int &ref)
{
    ref = 20;
}

int main()
{

    number a = 10;
    int &b = a;
    int *c = &a;
    cout << "Numbers a:" << a << "  b:" << b << "  c:" << *c;

    changeVar(b);
    cout << "\na: " << a;

    Person person1;
    person1.name = "Shri";
    person1.age = 22;
    cout << "\nName: " << person1.name << " Age: " << person1.age << "\n";

    cout << alignof(Person) << endl;
    cout << sizeof(Person) << endl;
    cout << alignof(MyStruct) << endl;
    cout << sizeof(MyStruct) << endl;
    cout << sizeof(string) << endl;

    return 0;
}