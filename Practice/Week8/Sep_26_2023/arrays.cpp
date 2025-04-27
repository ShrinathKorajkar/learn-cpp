#include <iostream>
#include <array>
#include <algorithm>

/*
    list = 24
    vector = 24
    pqueue = 32
    stack = 80
    queue = 80
    deque = 80
    array = sizeofelements
    set = 48
    map = 48
    uset = 56
    umap = 56
 */

int main()
{
    std::array<int, 5> myArray = {5, 2, 7, 1, 9};

    std::cout << "Element at index 2: " << myArray[2] << std::endl;

    try
    {
        std::cout << "Element at index 6: " << myArray.at(6) << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Out of range exception: " << e.what() << std::endl;
    }

    std::cout << "First element: " << myArray.front() << std::endl;
    std::cout << "Last element: " << myArray.back() << std::endl;

    std::cout << "Array size: " << myArray.size() << std::endl;
    std::cout << "Array max size: " << myArray.max_size() << std::endl;

    std::sort(myArray.begin(), myArray.end());

    std::cout << "Sorted array elements: ";
    for (const auto &element : myArray)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    std::array<int, 5> anotherArray = {1, 2, 3, 4, 5};
    if (myArray == anotherArray)
    {
        std::cout << "Arrays are equal." << std::endl;
    }
    else
    {
        std::cout << "Arrays are not equal." << std::endl;
    }

    return 0;
}
