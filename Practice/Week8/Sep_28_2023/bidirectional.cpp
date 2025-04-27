#include <iostream>
#include <list>
#include <set>

int main()
{
    std::list<int> numbers = {1, 2, 3, 4, 5};

    for (std::list<int>::iterator it = numbers.begin(); it != numbers.end(); ++it)
    {
        std::cout << *it << " ";
    }

    std::set<int> mySet = {1, 2, 3, 4, 5};

    for (std::set<int>::iterator it = mySet.begin(); it != mySet.end(); ++it)
    {
        std::cout << *it << " ";
    }

    return 0;
}
