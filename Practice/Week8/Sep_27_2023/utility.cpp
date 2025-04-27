#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main()
{
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int> doubled_numbers;

    std::transform(numbers.begin(), numbers.end(), std::back_inserter(doubled_numbers), [](int x)
                   { return 2 * x; });

    for (int num : doubled_numbers)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "Sum: " << sum << std::endl;

    auto min_it = std::min_element(numbers.begin(), numbers.end());
    auto max_it = std::max_element(numbers.begin(), numbers.end());

    std::cout << "Minimum: " << *min_it << std::endl;
    std::cout << "Maximum: " << *max_it << std::endl;

    std::fill(numbers.begin(), numbers.end(), 42);
    std::vector<int> destination(5);

    std::copy(numbers.begin(), numbers.end(), destination.begin());
    for (int num : destination)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
