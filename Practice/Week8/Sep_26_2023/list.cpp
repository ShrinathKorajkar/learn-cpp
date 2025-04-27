#include <iostream>
#include <list>

int main()
{
    std::list<int> myList = {1, 2, 3, 4};

    std::list<int>::iterator it = std::next(myList.begin());

    myList.insert(myList.begin(), 1);
    myList.insert(it, 5); // remain valid, check by replacing list with vector

    for (const auto &num : myList)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // splice
    std::list<int> myList1 = {1, 2, 3};
    std::list<int> myList2 = {4, 5};

    it = myList1.begin();
    std::advance(it, 2);
    myList1.splice(it, myList2);

    for (const auto &num : myList1)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Other
    myList2 = {1, 1, 2, 2, 3, 4, 4, 5, 5};
    myList2.remove(2);
    myList2.remove_if([](int num)
                      { return num % 2 == 0; });

    myList2.unique();
    myList2.merge(myList); // merge in sorted order

    for (const auto &num : myList2)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << std::endl
              << sizeof(myList) << std::endl;

    return 0;
}
