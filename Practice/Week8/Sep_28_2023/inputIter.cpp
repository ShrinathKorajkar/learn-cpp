#include <iostream>
#include <vector>

int main()
{
    int value;
    if (std::cin >> value)
    {
        std::cout << "Read: " << value << std::endl;
    }

    std::vector<int> numbers = {1, 2, 3, 4, 5};
    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
