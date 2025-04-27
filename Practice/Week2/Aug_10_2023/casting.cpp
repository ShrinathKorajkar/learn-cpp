#include <iostream>

int main()
{
    // static
    int num = 42;
    double result = static_cast<double>(num);

    std::cout << "static_cast result: " << result << std::endl;

    const int num2 = 42;

    // const_cast example
    int *nonConstPtr = const_cast<int *>(&num2);
    *nonConstPtr = 99;

    // reinterpret_cast example
    void *voidPtr = reinterpret_cast<void *>(&num);
    int *numPtr = reinterpret_cast<int *>(voidPtr);

    std::cout << "numPtr value: " << *numPtr << std::endl;
    return 0;
}