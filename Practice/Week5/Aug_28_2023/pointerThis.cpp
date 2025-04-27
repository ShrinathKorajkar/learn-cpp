#include <iostream>

class MyClass
{
public:
    int a;
    void display()
    {
        std::cout << "a: " << a << std::endl;
    }
};

int main()
{
    int MyClass::*ptr = &MyClass::a;
    void (MyClass::*ptrFunc)() = &MyClass::display;

    MyClass obj;
    obj.*ptr = 10;
    (obj.*ptrFunc)();
    return 0;
}