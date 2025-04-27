#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>

int main()
{
    std::vector<int> myVec = {9, 2, 5, 2, 5, 6, 6, 7, 3, 2, 1, 4};
    std::list<int> list = {9, 2, 5, 2, 5, 6, 6, 7, 3, 2, 1, 4};
    std::deque<int> deque = {9, 2, 5, 2, 5, 6, 6, 7, 3, 2, 1, 4};
    std::set<int> set = {9, 2, 5, 2, 5, 6, 6, 7, 3, 2, 1, 4};

    int target = 3;

    auto predicateFunc = [](int x)
    { return x % 2 == 0; };

    std::sort(myVec.begin(), myVec.end());

    bool found = std::binary_search(myVec.begin(), myVec.end(), target);
    int count = std::count(myVec.begin(), myVec.end(), target);
    int evenCount = std::count_if(myVec.begin(), myVec.end(), predicateFunc);
    std::vector<int>::iterator findIt = std::find(myVec.begin(), myVec.end(), target);
    std::vector<int>::iterator findIfIt = std::find_if(myVec.begin(), myVec.end(), predicateFunc);
    std::vector<int> searchSet = {2, 7};
    std::vector<int>::iterator findFirstOfIt = std::find_first_of(myVec.begin(), myVec.end(), searchSet.begin(), searchSet.end());
    std::vector<int> subVec = {3, 4};
    std::vector<int>::iterator searchIt = std::search(myVec.begin(), myVec.end(), subVec.begin(), subVec.end());
    std::vector<int>::iterator adjacentFindIt = std::adjacent_find(myVec.begin(), myVec.end());
    std::vector<int>::iterator lowerBoundIt = std::lower_bound(myVec.begin(), myVec.end(), target);
    std::vector<int>::iterator upperBoundIt = std::upper_bound(myVec.begin(), myVec.end(), target);
    std::pair<std::vector<int>::iterator, std::vector<int>::iterator> equalRange = std::equal_range(myVec.begin(), myVec.end(), target);

    std::cout << "Binary Search: " << (found ? "Found" : "Not Found") << std::endl;
    std::cout << "Count of " << target << ": " << count << std::endl;
    std::cout << "Count of even numbers: " << evenCount << std::endl;
    std::cout << "Find: " << *findIt << std::endl;
    std::cout << "Find If (even): " << *findIfIt << std::endl;
    std::cout << "Find First Of (2 or 7): " << *findFirstOfIt << std::endl;
    std::cout << "Search (3, 4): " << *searchIt << std::endl;
    std::cout << "Adjacent Find: " << *adjacentFindIt << std::endl;
    std::cout << "Lower Bound: " << *lowerBoundIt << std::endl;
    std::cout << "Upper Bound: " << *upperBoundIt << std::endl;
    std::cout << "Equal Range: [" << *equalRange.first << ", " << *equalRange.second << "]" << std::endl;

    return 0;
}
