#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<int> numbers = {1, 2, 3};
    std::vector<int> newNumbers;

    std::copy(numbers.begin(), numbers.end(), std::back_inserter(newNumbers));

    for (const auto &num : newNumbers)
    {
        std::cout << num << " ";
    }

    std::istream_iterator<int> inputIter(std::cin);
    std::istream_iterator<int> endOfInput;

    while (inputIter != endOfInput)
    {
        numbers.push_back(*inputIter);
        ++inputIter;
    }

    std::ostream_iterator<int> outputIter(std::cout, " ");
    for (const auto &num : numbers)
    {
        *outputIter++ = num;
    }

    numbers = {1, 2, 3, 4, 5};
    for (auto it = numbers.rbegin(); it != numbers.rend(); ++it)
    {
        std::cout << *it << " ";
    }

    std::vector<int> source = {1, 2, 3};
    std::vector<int> destination;

    std::move(source.begin(), source.end(), std::back_inserter(destination));

    for (const auto &num : destination)
    {
        std::cout << num << " ";
    }

    return 0;
}
