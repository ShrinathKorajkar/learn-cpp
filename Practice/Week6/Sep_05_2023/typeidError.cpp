#include <iostream>

void createBadTypeId(int choice)
{
    switch (choice)
    {
    case 2:
        std::__throw_bad_function_call();
        break;
    case 1:
        throw std::bad_typeid();
        break;
    }
}

int main()
{
    try
    {
        createBadTypeId(2);
    }
    catch (const std::bad_typeid &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}