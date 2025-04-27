#include <iostream>
#define NDEBUG
#include <cassert>

int divide(int a, int b)
{
    assert(b != 0 && "Division by zero is not allowed");
    return a / b;
}

int main()
{

    int result = divide(10, 2);
    result = divide(10, 0);
    std::cout << result << std::endl;

    return 0;
}
