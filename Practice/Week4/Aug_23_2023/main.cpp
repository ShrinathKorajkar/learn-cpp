#include <iostream>
#include <headerClass.hpp>

int main()
{
    Date today(2023, 06, 23);
    std::cout << today.getDay() << "/" << today.getMonth() << "/" << today.getYear() << std::endl;
    return 0;
}