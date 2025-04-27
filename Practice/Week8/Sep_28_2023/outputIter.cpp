#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main()
{
    std::vector<int> numbers;
    std::back_insert_iterator<std::vector<int>> outputIterator(numbers);

    for (int i = 0; i < 3; i++)
    {
        *outputIterator = i;
        ++outputIterator;
    }

    std::for_each(numbers.begin(), numbers.end(), [](int &num)
                  { num = num * num; });

    for (int num : numbers)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::ostream_iterator<int> outputIterator(std::cout, " ");
    std::copy(numbers.begin(), numbers.end(), outputIterator);

    std::vector<int> destination;
    std::copy(numbers.begin(), numbers.end(), std::back_inserter(destination));

    return 0;
}
