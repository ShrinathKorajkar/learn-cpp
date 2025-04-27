#include <iostream>
#include <vector>
#include <algorithm>

auto add = [](const int &a, const int &b) -> int
{ return a + b; };

auto multiply = [](const int &a, const int &b)
{ return a * b; };

int main()
{
    int x = 10, y = 20;
    auto lambdaWithCapture = [x, &y](const int &a)
    {
        y = 20;
        // x = 10;      error ->  const lambda
        return a * x + y;
    };
    auto subtract = [=](const int &a, const int &b) mutable
    {
        x = 10;
        return a - b + 10;
    };

    std::cout << "add : " << add(3, 4) << std::endl;
    std::cout << "mul : " << multiply(3, 4) << std::endl;
    std::cout << "cap : " << lambdaWithCapture(3) << std::endl;
    std::cout << "sub : " << subtract(3, 4) << std::endl;

    std::vector<int> list = {1, 2, 3};
    std::for_each(list.begin(), list.end(), [](int i)
                  { std::cout << i << " "; });
    std::cout << std::endl;
    return 0;
}