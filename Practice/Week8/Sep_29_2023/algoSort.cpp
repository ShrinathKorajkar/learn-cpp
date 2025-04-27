#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>

struct Person
{
    std::string name;
    int age;
};

bool personComparator(const Person &p1, const Person &p2)
{
    return p1.age < p2.age;
}

int main()
{
    // custom class sort
    Person people[] = {{"Alice", 25}, {"Bob", 30}, {"Charlie", 20}};
    int size = sizeof(people) / sizeof(people[0]);
    std::sort(people, people + size, personComparator);

    std::vector<int> myVec = {9, 2, 5, 2, 5, 6, 7, 3, 2, 1, 9};
    std::vector<std::string> stringVec = {"shri", "ram", "sena", "radha"};
    std::deque<int> deque = {9, 2, 5, 2, 5, 6, 7, 3, 2, 1, 9};
    std::list<int> list = {9, 2, 5, 2, 5, 6, 7, 3, 2, 1, 9};
    std::forward_list<int> forward_list = {9, 2, 5, 2, 5, 6, 7, 3, 2, 1, 9};

    // Introsort - inplace
    std::sort(myVec.begin(), myVec.end());
    std::sort(stringVec.begin(), stringVec.end());
    std::sort(deque.begin(), deque.end());

    list.sort();
    forward_list.sort();

    for (auto val : stringVec)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // merge sort -  stable sort
    std::stable_sort(myVec.begin(), myVec.end());
    std::stable_sort(stringVec.begin(), stringVec.end());
    std::stable_sort(deque.begin(), deque.end());

    // heap sort - inplace
    std::vector<int> numbers = {5, 2, 9, 1, 5};
    std::make_heap(numbers.begin(), numbers.end());
    std::sort_heap(numbers.begin(), numbers.end());

    return 0;
}