#include <iostream>
#include <queue>

int main()
{
    std::queue<int> myQueue;

    myQueue.push(1);
    myQueue.push(2);
    myQueue.push(3);

    std::cout << "Front element: " << myQueue.front() << std::endl;

    myQueue.pop();
    std::cout << "After pop, front element: " << myQueue.front() << std::endl;

    std::cout << "Queue size: " << myQueue.size() << std::endl;

    std::cout << std::endl
              << sizeof(myQueue) << std::endl;

    return 0;
}
