#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

template <typename T>
void print(const T &container)
{
    for (auto val : container)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int generateValue()
{
    static int i = 0;
    return i++;
}

int main()
{
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    std::vector<int> copyOfNumbers(numbers.size());
    std::vector<int> movedNumbers(numbers.size());

    std::copy(numbers.begin(), numbers.end(), copyOfNumbers.begin());

    std::move(numbers.begin(), numbers.end(), movedNumbers.begin());

    std::swap(numbers[0], numbers[1]);

    std::vector<int> otherNumbers = {10, 20, 30, 40, 50};
    std::swap_ranges(numbers.begin(), numbers.begin() + 3, otherNumbers.begin());

    std::vector<int>::iterator it1 = numbers.begin();
    std::vector<int>::iterator it2 = otherNumbers.begin();
    std::iter_swap(it1, it2);

    std::fill(numbers.begin(), numbers.end(), 42);

    std::fill_n(numbers.begin(), 3, 7);

    std::replace(numbers.begin(), numbers.end(), 7, 77);

    numbers.erase(std::remove(numbers.begin(), numbers.end(), 77), numbers.end());

    std::sort(numbers.begin(), numbers.end());
    auto newEnd = std::unique(numbers.begin(), numbers.end());
    numbers.resize(std::distance(numbers.begin(), newEnd));

    std::reverse(numbers.begin(), numbers.end());

    std::rotate(movedNumbers.begin(), movedNumbers.begin() + 3, movedNumbers.end());

    std::cout << "Permutations of Numbers : " << std::endl;
    do
    {
        for (const int &num : otherNumbers)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    } while (std::next_permutation(otherNumbers.begin(), otherNumbers.end()));

    auto partitionPredicate = [](int x)
    { return x % 2 == 0; };
    std::partition(movedNumbers.begin(), movedNumbers.end(), partitionPredicate);

    std::sort(movedNumbers.begin(), movedNumbers.end());

    std::stable_sort(copyOfNumbers.begin(), copyOfNumbers.end());

    std::shuffle(movedNumbers.begin(), movedNumbers.end(), std::default_random_engine());

    std::partial_sort(movedNumbers.begin(), movedNumbers.begin() + 5, movedNumbers.end());

    std::vector<int> sortedNumbers = {1, 13, 15, 17, 19};
    std::vector<int> merged(numbers.size() + sortedNumbers.size());
    std::merge(numbers.begin(), numbers.end(), sortedNumbers.begin(), sortedNumbers.end(), merged.begin());

    std::inplace_merge(sortedNumbers.begin(), sortedNumbers.end(), merged.end());

    std::cout << "numbers  : ";
    print(numbers);
    std::cout << "Moved No : ";
    print(movedNumbers);
    std::cout << "other No : ";
    print(otherNumbers);
    std::cout << "copy nos : ";
    print(copyOfNumbers);
    std::cout << "merged no: ";
    print(merged);
    std::cout << "Sorted no: ";
    print(sortedNumbers);

    std::generate(otherNumbers.begin(), otherNumbers.end(), generateValue);
    std::cout << "Generated: ";
    print(otherNumbers);

    return 0;
}
