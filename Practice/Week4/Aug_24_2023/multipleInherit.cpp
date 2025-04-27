#include <iostream>

class A
{
public:
    A() { std::cout << "Const A" << std::endl; }
    ~A() { std::cout << "Dest A" << std::endl; }
};

class B
{
public:
    B() { std::cout << "Const B" << std::endl; }
    ~B() { std::cout << "Dest B" << std::endl; }
};

class C : public A, public B
{
public:
    C() { std::cout << "Const C" << std::endl; }
    ~C() { std::cout << "Dest C" << std::endl; }
};

int main()
{
    C c;
    return 0;
}