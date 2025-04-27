#include <iostream>
#include "header1.h"
#include "header2.hpp"
/*
    g++ -o output/myHeader *.cpp
    ./output/myHeader
*/
int main()
{
    printMessage();
    myNamespace::myFunction();

    printSecretInfo();

    std::cout << add(4, 5) << std::endl;
    return 0;
}
