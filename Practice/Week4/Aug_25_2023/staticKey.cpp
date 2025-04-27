#include <iostream>

int a{};
static int b{};
static void greet()
{
    int c{};
    static int d{}; // stored in data segment as greet()::d
    std::cout << "greet a:" << a++ << ", b:" << b++ << ", c:" << c++ << ", d:" << d++ << std::endl;
}

class A
{

public:
    int e{};
    static const int f{};
    static int g;
    void hello()
    {
        std::cout << "Ahello a:" << a++ << ", b:" << b++ << ", e:" << e++ << ", g:" << g++ << std::endl;
    }
    static void greet()
    {
        std::cout << "Agreet a:" << a++ << ", b:" << b++ << ", f:" << f << ", g:" << g++ << std::endl;
    }
};

int A::g = 0; // data segment A::g

int main()
{
    greet();
    greet();
    greet();

    A aa;
    A bb;
    aa.hello();
    aa.hello();
    bb.hello();
    bb.hello();

    aa.greet();
    aa.greet();
    bb.greet();
    bb.greet();

    std::cout << "main   a:" << a << ", b:" << b << ", f:" << A::f << ", g:" << A::g << std::endl;
    A::greet();
    return 0;
}