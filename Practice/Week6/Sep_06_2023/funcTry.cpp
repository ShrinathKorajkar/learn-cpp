#include <iostream>

class A
{
public:
    A(int)
    try
    {
        throw 5;
    }
    catch (int)
    {
        std::cerr << "handled in A" << std::endl;
        throw;
    }
    ~A() { std::cout << "A" << std::endl; }
};

class B : public A
{
public:
    B()
    try : A(5)
    {
    }
    catch (int)
    {
        std::cerr << "handled in B" << std::endl;
    }
    ~B() { std::cout << "B" << std::endl; }
};
int main()
{
    try
    {
        B b;
    }
    catch (int)
    {
        std::cerr << "Handled in main" << std::endl;
    }
    return 0;
}