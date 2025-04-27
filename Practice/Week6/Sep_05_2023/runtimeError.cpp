#include <iostream>
#include <system_error>

void createRuntimeErrors(int choice)
{
    switch (choice)
    {
    case 1:
        throw std::range_error("Index out of bounds"); // int is having specific range
        break;
    case 2:
        throw std::overflow_error("stack overflow");
        break;
    case 3:
        throw std::underflow_error("stack underflow");
    case 4:
        throw std::system_error(ENFILE, std::system_category(), "System error");
        break;
    }
}

int main()
{
    try
    {
        createRuntimeErrors(4);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}