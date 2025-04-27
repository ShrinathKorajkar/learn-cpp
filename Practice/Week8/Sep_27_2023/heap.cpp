#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> heap = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    std::make_heap(heap.begin(), heap.end());

    heap.push_back(10);
    std::push_heap(heap.begin(), heap.end());

    std::pop_heap(heap.begin(), heap.end());
    int max = heap.back();
    heap.pop_back();

    std::sort_heap(heap.begin(), heap.end());

    for (const auto &element : heap)
    {
        std::cout << element << " ";
    }

    std::cout << "\nMaximum: " << max << std::endl;

    return 0;
}
