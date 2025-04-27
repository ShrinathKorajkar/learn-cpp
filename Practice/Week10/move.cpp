#include <iostream>
#include <vector>

void overloaded(int &x) { std::cout << "[lvalue] " << x << std::endl; }
void overloaded(int &&x) { std::cout << "[rvalue] " << x << std::endl; }

template <class T>
void fn(T &&x)
{
    overloaded(x);                  // always an lvalue
    overloaded(std::move(x));       // always an rvalue
    overloaded(std::forward<T>(x)); // rvalue if argument is rvalue
}

int main()
{
    std::vector<int> source = {1, 2, 3};
    std::vector<int> destination = std::move(source);

    std::cout << "source : " << source.size() << std::endl;
    std::cout << "destination : " << destination.size() << std::endl;
    std::cout << "destination : ";
    for (auto value : destination)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    //
    int a = 1;
    fn(a);
    fn(2);
    return 0;
}