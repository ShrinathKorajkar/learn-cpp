#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

int add(int a, int b)
{
    return a + b;
}

class SomeClass
{
public:
    int memberFunction(int x)
    {
        return x * 2;
    }
};

int main()
{
    auto add5 = std::bind(add, 5, std::placeholders::_1);
    std::cout << add5(3) << std::endl;

    std::function<int(int, int)> func = add;
    std::cout << func(3, 4) << std::endl;

    std::function<void()> callback;
    callback = []()
    { std::cout << "Callback 1" << std::endl; };
    callback();

    callback = []()
    { std::cout << "Callback 2" << std::endl; };
    callback();

    std::vector<std::function<void(int)>> callbacks;
    callbacks.push_back([](int x)
                        { std::cout << "Callback 3: " << x << std::endl; });
    callbacks.push_back([](int x)
                        { std::cout << "Callback 4: " << x * 2 << std::endl; });
    for (auto &cb : callbacks)
    {
        cb(42);
    }

    SomeClass obj;
    auto memberFunc = std::bind(&SomeClass::memberFunction, &obj, std::placeholders::_1);
    int value = memberFunc(7);
    std::cout << "Member Function Result: " << value << std::endl;

    std::vector<std::pair<int, int>> pairs = {{1, 4}, {2, 2}, {3, 1}};
    std::sort(pairs.begin(), pairs.end(), std::bind(std::greater<int>(), std::bind(&std::pair<int, int>::second, std::placeholders::_1), std::bind(&std::pair<int, int>::second, std::placeholders::_2)));

    std::cout << "Sorted Pairs by Second Element:" << std::endl;
    for (const auto &pair : pairs)
    {
        std::cout << pair.first << ", " << pair.second << std::endl;
    }

    return 0;
}
