#include <iostream>
#include <algorithm>

int main()
{
    std::string abc = "abcd";
    std::reverse(abc.begin(), abc.end());
    std::cout << abc << std::endl;
    return 0;
}