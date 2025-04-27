#include <iostream>

template <int N>
struct Factorial
{
    static constexpr int value = N * Factorial<N - 1>::value;
};

template <>
struct Factorial<0>
{
    static constexpr int value = 1;
};

// compile time loop
static int sum = 0;
template <int N>
struct Loop
{
    static void execute()
    {
        sum++;
        Loop<N - 1>::execute();
    }
};

template <>
struct Loop<0>
{
    static void execute()
    {
        std::cout << "sum = " << sum << std::endl;
    }
};

int main()
{
    constexpr int result = Factorial<5>::value;
    std::cout << result << std::endl;

    Loop<5>::execute();
    return 0;
}
