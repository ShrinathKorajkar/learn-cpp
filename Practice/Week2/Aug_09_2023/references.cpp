#include <iostream>
#include <utility>

void passbyreference(int &a, const int &b)
{
    a = b;
}

// int &returnDanglingReference()
// {
//     int x = 23;
//     return x;
// }

void printRef(int &a)
{
    std::cout << "LRef : " << a << std::endl;
}

void printRef(int &&a)
{
    std::cout << "RRef : " << a << std::endl;
}

// Perfect Forwarding
void foo(int &x)
{
    std::cout << x << std::endl;
}

template <typename T>
void wrapper(T &&arg)
{
    foo(std::forward<T>(arg));
}

int main()
{
    int original = 10;
    int &reference = original;

    std::cout << reference << std::endl;

    // reference to const
    const int constant = 20;
    const int &refConst = constant;
    std::cout << refConst << std::endl;

    passbyreference(reference, refConst);
    std::cout << original << std::endl;

    // int &danglindRef = returnDanglingReference();

    const int &constRef = 10;
    std::cout << constRef << std::endl;

    int &&RvalueRef = 2 + 3;
    std::cout << RvalueRef << std::endl;

    //
    printRef(original);
    printRef(30);

    //
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7};
    for (auto &num : arr)
    {
        num *= 2;
    }
    for (auto num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Move Semantics
    std::string source("Hello");
    std::string destination = std::move(source);

    // Perfect Forwarding
    int x = 42;
    wrapper(x);
    return 0;
}
