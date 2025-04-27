#include <iostream>
#include "header.h"

template <typename T>
MyClass<T>::MyClass(T data) : m_data(data) {}

template <typename T>
void greet(T value)
{
    std::cout << value << std::endl;
}

template class MyClass<int>;
template void greet(int value);