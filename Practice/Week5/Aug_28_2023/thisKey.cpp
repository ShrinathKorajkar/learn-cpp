#include <iostream>

class A
{
    int a = 1;
    int b = this->a;
    int c = 2;
    int d;

public:
    A() : d(this->c)
    {
        b = this->c;
        std::cout << "a : " << a << std::endl;
        std::cout << "b : " << b << std::endl;
    }
    void printValues()
    {
        std::cout << "c : " << this->c << std::endl;
        std::cout << "d : " << this->d << std::endl;
    }

    void values()
    {
        this->printValues();
        (*this).printValues();
    }
};

int main()
{
    A a;
    a.values();

    return 0;
}