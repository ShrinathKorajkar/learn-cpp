#include <iostream>
#include <utility>

void process(int &&rvalue)
{
    std::cout << "Received rvalue : " << rvalue << std::endl;
    rvalue += 10;
}

template <typename T>
void forwarder(T &&value)
{
    process(std::forward<T>(value)); // if we don't use this it will be call lvalue reference
}

void printLValue(int &lvalue)
{
    std::cout << "lvalue : " << lvalue << std::endl;
}

void printConstLValue(const int &lvalue)
{
    std::cout << "const lvalue : " << lvalue << std::endl;
}

void printRValue(int &&lvalue)
{
    std::cout << "rvalue : " << lvalue << std::endl;
}

int main()
{
    int x = 42;
    process(52);
    process(std::move(x));
    std::cout << "x after processing : " << x << std::endl;
    forwarder(std::move(x));
    std::cout << "x after processing : " << x << std::endl;

    // int &a = 10; // error
    const int &a = 10; // rvalue bound to const lvalue ref

    // l value
    // printLValue(a);
    // printLValue(10);
    printLValue(x);

    // const l value
    printConstLValue(a);
    printConstLValue(10);
    printConstLValue(x);

    // r value
    // printRValue(a);
    printRValue(10);
    // printRValue(x);
    return 0;
}