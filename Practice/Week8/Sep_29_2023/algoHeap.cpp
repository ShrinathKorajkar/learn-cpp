#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

template <typename T>
void print(const T &container)
{
    for (auto val : container)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5};

    std::make_heap(vec.begin(), vec.end());

    std::cout << "Max heap: ";
    print(vec);

    vec.push_back(7);
    std::push_heap(vec.begin(), vec.end());

    std::cout << "Max heap after push: ";
    print(vec);

    std::pop_heap(vec.begin(), vec.end());
    int max_element = vec.back();
    vec.pop_back();

    std::cout << "Popped max element: " << max_element << std::endl;

    std::sort_heap(vec.begin(), vec.end());

    std::cout << "Sorted elements: ";
    print(vec);

    if (std::is_heap(vec.begin(), vec.end()))
    {
        std::cout << "The range is a valid heap." << std::endl;
    }
    else
    {
        std::cout << "The range is not a valid heap." << std::endl;
    }

    auto heap_end = std::is_heap_until(vec.begin(), vec.end());
    std::cout << "The largest subrange forming a valid heap ends at position: " << (heap_end - vec.begin()) << std::endl;

    std::priority_queue<int> pq(vec.begin(), vec.end());

    std::cout << "Priority Queue (max heap): ";
    while (!pq.empty())
    {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << std::endl;

    return 0;
}
