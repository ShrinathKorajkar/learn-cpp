#include <iostream>

template <typename T>
class Base
{
public:
    T data;
    Base(T data) : data(data) {}
    virtual ~Base() {}
    virtual void printData() = 0;
};

template <typename T>
class Derived : public Base<T>
{
public:
    Derived(T data) : Base<T>(data) {}
    void printData() override { std::cout << "Derived : " << this->data << std::endl; }
};

int main()
{
    Base<int> *ptr = new Derived(42);
    ptr->printData();
    delete ptr;
    return 0;
}