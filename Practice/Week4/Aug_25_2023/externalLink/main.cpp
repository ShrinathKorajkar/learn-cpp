#include <iostream>

extern int nonStaticVar;
extern void nonStaticFunction();
extern void staticFunction();
extern int staticVar;

int main()
{
    std::cout << "Inside main" << std::endl;
    std::cout << "Non-Static var : " << nonStaticVar << std::endl;
    nonStaticFunction();
    // std::cout << "Static var : " << staticVar << std::endl; // error -> undefined reference
    // staticFunction();                                       // error -> undefined reference
    return 0;
}
