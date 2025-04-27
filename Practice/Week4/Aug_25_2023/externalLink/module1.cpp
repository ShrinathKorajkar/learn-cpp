#include <iostream>

static int staticVar = 10; // internal linking
int nonStaticVar = 20;     // external linking

void nonStaticFunction()
{
    std::cout << "Inside non static function : " << std::endl;
    std::cout << "static var : " << staticVar << std::endl;
    std::cout << "Non Static var : " << nonStaticVar << std::endl;
}

static void staticFunction()
{
    std::cout << "Inside static function" << std::endl;
    std::cout << "static var : " << staticVar << std::endl;
    std::cout << "Non Static var : " << nonStaticVar << std::endl;
}
