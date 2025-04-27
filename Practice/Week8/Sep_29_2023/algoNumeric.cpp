#include <iostream>
#include <algorithm>
#include <numeric>
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
    std::vector<int> numbers = {8, 9, 10, 4, 5, 6, 7, 1, 2, 3};
    std::vector<int> partial_sums(numbers.size());
    std::vector<int> exclusive_prefix(numbers.size());
    std::vector<int> inclusive_prefix(numbers.size());
    std::vector<int> iota(numbers.size());
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {2, 4, 6};
    std::vector<int> differences(numbers.size());

    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);

    std::partial_sum(numbers.begin(), numbers.end(), partial_sums.begin());

    std::exclusive_scan(numbers.begin(), numbers.end(), exclusive_prefix.begin(), 0);

    std::inclusive_scan(numbers.begin(), numbers.end(), inclusive_prefix.begin(), [](int current_sum, int element)
                        { return current_sum + element; });

    int inner_product_result = std::inner_product(v1.begin(), v1.end(), v2.begin(), 0);

    int transform_reduce_result = std::transform_reduce(v1.begin(), v1.end(), v2.begin(), 0);
    // Result: (1*2 + 2*4 + 3*6) + 0 = 28

    std::adjacent_difference(numbers.begin(), numbers.end(), differences.begin());

    std::iota(iota.begin(), iota.end(), 1);
    // assigns a sequence of incrementing values from 1 -> Result: iota = {1, 2, 3, 4, 5}

    int common_divisor = std::gcd(12, 18);
    int common_multiple = std::lcm(4, 6);

    auto min_element_iterator = std::min_element(numbers.begin(), numbers.end());
    auto max_element_iterator = std::max_element(numbers.begin(), numbers.end());

    int min_value = std::min(42, 56);
    int max_value = std::max(23, 89);

    int clamped_value = std::clamp(7, 3, 8);
    // restrict (clamp, low, high)
    // return  clamp => low < clamp < high
    // return  low   => clamp < low
    // return  high  => clamp > high

    int count = std::count(numbers.begin(), numbers.end(), 5);

    bool sorted = std::is_sorted(numbers.begin(), numbers.end());

    bool partitioned = std::is_partitioned(numbers.begin(), numbers.end(), [](int x)
                                           { return x % 2 == 0; });

    std::nth_element(numbers.begin(), numbers.begin() + 5, numbers.end());
    //(first, nth, last) =>  convert it into BST with nth element as root

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Inner Product: " << inner_product_result << std::endl;
    std::cout << "Partial Sums: ";
    print(partial_sums);
    std::cout << "Exclusive Prefix Sum: ";
    print(exclusive_prefix);
    std::cout << "Inclusive Prefix Sum: ";
    print(inclusive_prefix);
    std::cout << "Transform Reduce Result: " << transform_reduce_result << std::endl;
    std::cout << "Adjacent Differences: ";
    print(differences);
    std::cout << "Iota: ";
    print(iota);
    std::cout << "GCD: " << common_divisor << std::endl;
    std::cout << "LCM: " << common_multiple << std::endl;
    std::cout << "Min Element: " << *min_element_iterator << std::endl;
    std::cout << "Max Element: " << *max_element_iterator << std::endl;
    std::cout << "Min Value: " << min_value << std::endl;
    std::cout << "Max Value: " << max_value << std::endl;
    std::cout << "Clamped Value: " << clamped_value << std::endl;
    std::cout << "Count of 5: " << count << std::endl;
    std::cout << "Is Sorted: " << std::boolalpha << sorted << std::endl;
    std::cout << "Is Partitioned: " << std::boolalpha << partitioned << std::endl;
    std::cout << "nth_element: ";
    print(numbers);

    return 0;
}
