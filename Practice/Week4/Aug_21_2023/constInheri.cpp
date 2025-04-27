#include <iostream>

class Base
{
public:
    Base() { std::cout << "Base constructor" << std::endl; }
};

class Member
{
public:
    Member() { std::cout << "Member constructor" << std::endl; }
};

class Derived : public Base
{
private:
    Member member;

public:
    Derived() : member(), Base() // warning
    {
        std::cout << "Derived constructor" << std::endl;
    }
};

int main()
{
    Derived d;
    return 0;
}