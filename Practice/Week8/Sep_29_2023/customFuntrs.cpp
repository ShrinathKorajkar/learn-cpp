#include <iostream>
#include <functional>

// deprecated in c++11
struct Doubler : public std::unary_function<int, int>
{
    int operator()(int x) const
    {
        return 2 * x;
    }
};

struct Adder : public std::binary_function<int, int, int>
{
    int operator()(int x, int y) const
    {
        return x + y;
    }
};

template <typename T>
struct GenericFunctor
{
    T operator()(T a, T b) const
    {
        return a + b;
    }
};

int main()
{
    Doubler doubler;
    int num = 5;
    int doubled = doubler(num);
    std::cout << "Original number: " << num << std::endl;
    std::cout << "Doubled number: " << doubled << std::endl;

    Adder adder;
    int num1 = 5;
    int num2 = 7;
    int sum = adder(num1, num2);
    std::cout << "Sum of " << num1 << " and " << num2 << " is " << sum << std::endl;

    GenericFunctor<int> intFunctor;
    int result1 = intFunctor(5, 3);
    std::cout << "Result with int: " << result1 << std::endl;

    GenericFunctor<double> doubleFunctor;
    double result2 = doubleFunctor(2.5, 1.3);
    std::cout << "Result with double: " << result2 << std::endl;

    return 0;
}
