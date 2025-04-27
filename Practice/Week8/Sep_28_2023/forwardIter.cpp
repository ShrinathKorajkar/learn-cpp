#include <iostream>
#include <list>
#include <forward_list>

int main()
{
    std::list<int> numbers = {1, 2, 3, 4, 5};

    for (std::list<int>::iterator it = numbers.begin(); it != numbers.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::forward_list<int> numbers2 = {1, 2, 3, 4, 5};

    for (std::forward_list<int>::iterator it = numbers2.begin(); it != numbers2.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}
