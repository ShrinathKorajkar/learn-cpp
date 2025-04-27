#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

class MyFunction
{
public:
    int operator()(int x, int y)
    {
        return x + y;
    }
};

struct CustomSort
{
    bool operator()(int a, int b)
    {
        return a % 10 < b % 10;
    }
};

struct CustomAccumulator
{
    int operator()(int accumulator, int value)
    {
        return accumulator + value;
    }
};

struct IsGreaterThan
{
    int threshold;
    IsGreaterThan(int val) : threshold(val) {}

    bool operator()(int num)
    {
        return num > threshold;
    }
};
int main()
{
    MyFunction add;
    int result = add(1, 2);
    std::cout << "add : " << result << std::endl;

    std::vector<int> numbers = {93, 15, 42, 78, 5};
    std::sort(numbers.begin(), numbers.end(), CustomSort());
    std::for_each(numbers.begin(), numbers.end(), [](auto val)
                  { std::cout << val << " "; });
    std::cout << std::endl;

    int sum = std::accumulate(numbers.begin(), numbers.end(), 0, CustomAccumulator());
    std::cout << "Sum: " << sum << std::endl;

    IsGreaterThan filter(12);
    std::remove_if(numbers.begin(), numbers.end(), filter);

    std::for_each(numbers.begin(), numbers.end(), [](auto val)
                  { std::cout << val << " "; });
    std::cout << std::endl;
    return 0;
}