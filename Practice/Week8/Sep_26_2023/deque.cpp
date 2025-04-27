#include <iostream>
#include <deque>

int main()
{
    std::deque<int> myDeque;

    myDeque.push_back(1);
    myDeque.push_back(2);
    myDeque.push_front(0);

    for (const auto &num : myDeque)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl
              << sizeof(myDeque) << std::endl;
    return 0;
}
