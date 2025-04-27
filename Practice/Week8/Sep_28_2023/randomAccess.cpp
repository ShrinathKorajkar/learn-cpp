#include <iostream>
#include <vector>
#include <array>

int main()
{
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int>::iterator it = numbers.begin();
    std::cout << it[2] << std::endl;

    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    std::array<int, 5>::iterator it2 = arr.begin();
    std::cout << it2[2] << std::endl;

    int *it3 = numbers.data();
    std::cout << it3[2] << std::endl;

    return 0;
}
