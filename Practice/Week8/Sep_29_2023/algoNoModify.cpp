#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "std::for_each : ";
    std::for_each(numbers.begin(), numbers.end(), [](int num)
                  { std::cout << num << " "; });
    std::cout << "\n";

    std::vector<int> anotherNumbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    bool areEqual = std::equal(numbers.begin(), numbers.end(), anotherNumbers.begin());
    std::cout << "Are the two vectors equal? " << (areEqual ? "Yes" : "No") << "\n";

    auto mismatchResult = std::mismatch(numbers.begin(), numbers.end(), anotherNumbers.begin());
    if (mismatchResult.first != numbers.end())
    {
        std::cout << "Mismatch at position " << std::distance(numbers.begin(), mismatchResult.first) << "\n";
    }
    else
    {
        std::cout << "The two ranges are identical.\n";
    }

    bool allEven = std::all_of(numbers.begin(), numbers.end(), [](int num)
                               { return num % 2 == 0; });
    std::cout << "Are all numbers even? " << (allEven ? "Yes" : "No") << "\n";

    bool anyOdd = std::any_of(numbers.begin(), numbers.end(), [](int num)
                              { return num % 2 != 0; });
    std::cout << "Are there any odd numbers? " << (anyOdd ? "Yes" : "No") << "\n";

    bool noneNegative = std::none_of(numbers.begin(), numbers.end(), [](int num)
                                     { return num < 0; });
    std::cout << "Are there no negative numbers? " << (noneNegative ? "Yes" : "No") << "\n";

    std::vector<int> otherNumbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    bool isLexicographicallySmaller = std::lexicographical_compare(
        numbers.begin(), numbers.end(),
        otherNumbers.begin(), otherNumbers.end());
    std::cout << "Is numbers < otherNumbers lexicographically? " << (isLexicographicallySmaller ? "Yes" : "No") << "\n";

    std::vector<int> subsequence = {4, 5};
    auto foundEnd = std::find_end(numbers.begin(), numbers.end(), subsequence.begin(), subsequence.end());
    if (foundEnd != numbers.end())
    {
        std::cout << "Found subsequence at position " << std::distance(numbers.begin(), foundEnd) << "\n";
    }
    else
    {
        std::cout << "Subsequence not found.\n";
    }

    auto minmax = std::minmax_element(numbers.begin(), numbers.end());
    std::cout << "Minimum element: " << *minmax.first << "\n";
    std::cout << "Maximum element: " << *minmax.second << "\n";

    return 0;
}
