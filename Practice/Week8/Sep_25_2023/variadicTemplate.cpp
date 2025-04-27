#include <iostream>

template <typename... Args> // 0 or more arguments
void printArgs(Args... arg)
{
    ((std::cout << arg << " "), ...); // expansion
    std::cout << std::endl;
}

// RECURSION
// Base case
int sum()
{
    return 0;
}

// Recursive case
template <typename First, typename... Rest>
int sum(First first, Rest... rest)
{
    return first + sum(rest...); // return (arg + ...); with only one param
}

int main()
{
    int result = sum(1, 2, 3, 4, 5);
    std::cout << result << std::endl;

    printArgs(1, "hello", 2.33, '#');
    return 0;
}