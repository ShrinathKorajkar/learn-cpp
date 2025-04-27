#include <iostream>
#include <algorithm>
#include <vector>

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
    std::vector<int> set1 = {1, 2, 3, 4, 5};
    std::vector<int> set2 = {3, 4, 5, 6, 7};
    std::vector<int> result(set1.size() + set2.size());

    auto union_end = std::set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), result.begin());
    result.resize(union_end - result.begin());

    std::cout << "Union: ";
    print(result);

    auto intersection_end = std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), result.begin());
    result.resize(intersection_end - result.begin());

    std::cout << "Intersection: ";
    print(result);
    result.resize(set1.size() + set2.size());

    // present in set1 but not in set2
    auto difference_end = std::set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(), result.begin());
    result.resize(difference_end - result.begin());

    std::cout << "Difference: ";
    print(result);
    result.resize(set1.size() + set2.size());

    // present in either but not both
    auto symmetric_difference_end = std::set_symmetric_difference(set1.begin(), set1.end(), set2.begin(), set2.end(), result.begin());
    result.resize(symmetric_difference_end - result.begin());

    std::cout << "Symmetric Difference: ";
    print(result);

    if (std::includes(set1.begin(), set1.end(), set2.begin(), set2.end()))
    {
        std::cout << "set2 is a subset of set1." << std::endl;
    }
    else
    {
        std::cout << "set2 is not a subset of set1." << std::endl;
    }

    if (std::is_permutation(set1.begin(), set1.end(), set2.begin()))
    {
        std::cout << "set1 is a permutation of set2." << std::endl;
    }
    else
    {
        std::cout << "set1 is not a permutation of set2." << std::endl;
    }

    std::vector<int> merged_result(set1.size() + set2.size());
    std::merge(set1.begin(), set1.end(), set2.begin(), set2.end(), merged_result.begin());

    std::cout << "Merged Set: ";
    print(merged_result);

    return 0;
}
