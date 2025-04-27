#include <iostream>
#define replace(a, b, c, d) a##b##c##d
#define nomain replace(m, a, i, n)

int nomain()
{
    std::cout << "nomain" << std::endl;
    return 0;
}