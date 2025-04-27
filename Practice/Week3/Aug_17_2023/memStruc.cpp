#include <iostream>

int b;

int main(int argc, char **argv)
{

    std::cout << "Program Name : " << argv[0] << std::endl;
    for (int index = 1; index < argc; index++)
    {
        std::cout << "Argument " << index << " : " << argv[index] << std::endl;
    }

    std::cout << "Environment Variable : " << getenv("HOME") << std::endl;

    std::cout << "Global Variable : " << b << std::endl;

    int *ptr = new int(10);
    std::cout << "Var in heap memory : " << *ptr << std::endl;

    delete ptr;
    return 0;
}