/*
    function as pointers
*/
#include <iostream>
using namespace std;

int add(int a, int b)
{
    return a + b;
}

using OperationFunc = int (*)(int, int);

int calculate(OperationFunc func, int a, int b)
{
    return func(a, b);
}

// Function template
template <class SomeType>
SomeType sum(SomeType a, SomeType b)
{
    return a + b;
}

template <class T, int N>
T multiply(T a)
{
    return a * N;
}

// consteval -> strictly compile time evaluation
constexpr int add2(int x, int y)
{
    return x + y;
}

int getValue()
{
    return 4;
}

int main()
{

    int result = calculate(add, 10, 5); // Pass the add function as an argument
    cout << result << endl;

    int (*operation)(int, int);
    operation = add; // Assign the address of the add function to the function pointer
    result = operation(10, 5);
    cout << result << endl;

    int x = sum<int>(10, 20);
    cout << x << endl;

    x = multiply<int, 2>(10);
    cout << x << endl;

    //
    int a, b;
    std::cin >> a >> b;
    int result = add(a, b); // constexpr will be ignored
    cout << result << endl;

    constexpr int res = add2(5, 10); // Computed at compile time
    cout << res << endl;

    std::cout << getValue << '\n'; // return true
    return 0;
}
