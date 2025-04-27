#include <iostream>

class B;

class A
{
    int a{};
    friend class B;
};

class C : public A
{
    int c{};

public:
    // void disp(A &aa)
    // {
    //     std::cout << aa.a << std::endl;
    // }
};

class B
{
    int b{};
    A bb;

public:
    void display(A &aa, C &cc)
    {
        std::cout << aa.a << std::endl;
        std::cout << cc.a << std::endl; // cannot directly but through friend class
        // std::cout << cc.c << std::endl; // cannot access as friendship is not inherited
    }

    void hello()
    {
        std::cout << bb.a << std::endl;
    }
};

int main()
{
    A a;
    C c;
    B b;
    b.display(a, c);
    return 0;
}