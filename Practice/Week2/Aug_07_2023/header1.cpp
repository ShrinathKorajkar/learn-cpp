#include <iostream>
#include "header1.h"

void printMessage()
{
    std::cout << "Secret Message from header 1" << std::endl;
}

namespace myNamespace
{
    void myFunction()
    {
        std::cout << "Secret Message from MyNamespace" << std::endl;
    }
}