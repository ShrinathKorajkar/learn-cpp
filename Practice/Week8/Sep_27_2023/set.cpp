#include <iostream>
#include <set>

struct CostumComparator
{
    bool operator()(const int &a, const int &b) const
    {
        return a > b; // descending order
    }
};

int main()
{
    std::set<int> mySet = {9, 8, 7, 6, 5};

    for (int val : mySet)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    mySet.insert(10);
    mySet.insert({11, 1, 2, 3});
    mySet.erase(11);

    auto it = mySet.find(7);
    if (it != mySet.end())
    {
        std::cout << *it << std::endl;
    }

    mySet = {1, 2, 2, 3, 4, 5, 5, 5};
    int keyToCount = 5;
    int count = mySet.count(keyToCount);
    std::cout << "Element found 1 else 0 " << keyToCount << ": " << count << std::endl;
    auto lower = mySet.lower_bound(3);
    std::cout << "Lower bound for key 3: " << *lower << std::endl;
    auto upper = mySet.upper_bound(3);
    std::cout << "Upper bound for key 3: " << *upper << std::endl;
    auto range = mySet.equal_range(2);
    std::cout << "Elements matching key 2: ";
    for (auto it = range.first; it != range.second; ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::set<int>::key_compare keyComparator = mySet.key_comp();
    bool resultKeyComp = keyComparator(2, 4);
    std::cout << "Comparison using key_comp(): " << resultKeyComp << std::endl;
    std::set<int>::value_compare valueComparator = mySet.value_comp();
    bool resultValueComp = valueComparator(2, 4);
    std::cout << "Comparison using value_comp(): " << resultValueComp << std::endl;

    return 0;
}