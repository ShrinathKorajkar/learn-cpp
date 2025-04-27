#include <iostream>
#include <string>

template <typename T>
std::string returnStr(const T &value)
{
    return std::to_string(value);
}

template <typename T>
std::string returnStr(const T *value)
{
    return value;
}

template <> // specialization
std::string returnStr(const char &value)
{
    return std::string(1, value);
}

template <typename T, typename U>
void print(const T &value, const U &value1)
{
    std::cout << value << std::endl;
    std::cout << value1 << std::endl;
}

int main()
{
    std::cout << returnStr(1) << std::endl;
    std::cout << returnStr(1.1) << std::endl;
    std::cout << returnStr('@') << std::endl;
    std::cout << returnStr('a') << std::endl;
    std::cout << returnStr(true) << std::endl;
    std::cout << returnStr("false") << std::endl;
    return 0;
}