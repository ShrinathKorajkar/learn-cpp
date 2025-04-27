#include <iostream>
#include <queue>
#include <vector>

int main()
{
    std::priority_queue<int> maxHeap;

    maxHeap.push(3);
    maxHeap.push(1);
    maxHeap.push(4);

    std::cout << "Top element: " << maxHeap.top() << std::endl;
    maxHeap.pop();
    std::cout << "After pop, top element: " << maxHeap.top() << std::endl;

    //
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    minHeap.push(4);
    minHeap.push(1);
    minHeap.push(7);
    minHeap.push(2);
    minHeap.push(5);

    std::cout << "Min Heap Top : " << minHeap.top() << std::endl;

    std::cout << std::endl
              << sizeof(maxHeap) << std::endl;
    return 0;
}
