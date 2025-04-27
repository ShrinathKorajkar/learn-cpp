#include <iostream>
class Parent
{
public:
    int a;
};
class A : public Parent
{
    const int c = 10;
    const int a;
    const int b;

public:
    Parent *p = this;
    A() : a(c), b(this->a)
    {
        std::cout << this << std::endl;
        std::cout << p << std::endl;
        std::cout << b << std::endl;
        std::cout << c << std::endl;
        std::cout << sizeof(this) << std::endl;
    }
};

int main()
{
    A a;
    return 0;
}