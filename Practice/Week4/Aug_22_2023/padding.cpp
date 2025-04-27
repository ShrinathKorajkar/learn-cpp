#include <iostream>

// #pragma pack(4)
// #pragma pack(push, 4)
class Hello
{
public:
    char q;
    int a;
    char g;
    double b;
    char c;
};
// #pragma pack(pop) // Restore default packing

class alignas(16) Hi
{
    int a : 32;
    char c;
};

class __attribute__((packed)) HelloOnceAgain
{
    char q;
    int a;
    char g;
    double b;
    char c;
};

class ABC
{
public:
    int a;
};

int main()
{

    ABC b{.a = 1};
    std::cout << sizeof(Hello) << std::endl;
    std::cout << sizeof(Hi) << std::endl;
    std::cout << sizeof(HelloOnceAgain) << std::endl;
    return 0;
}
