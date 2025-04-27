#include <iostream>
template <typename T>
class MyGenericClass
{
    T data;

public:
    MyGenericClass(T data) : data(data) {}
    MyGenericClass() = default;
    T getData()
    {
        return data;
    }
    void setData(T data)
    {
        this->data = data;
    }
};

template <>
class MyGenericClass<float>
{
    float data;

public:
    MyGenericClass(float data) : data(data + 1.0) {}
    MyGenericClass() = default;
    float getData()
    {
        return data;
    }
    template <typename U>
    void setData(U data)
    {
        this->data = static_cast<float>(data);
    }
};

template class MyGenericClass<int>; // explicit instantiation

template <typename T = int, int N = 5>
class Array
{
    T data[N];

public:
    Array()
    {
        for (int i = 0; i < N; ++i)
        {
            data[i] = T(i);
        }
    }

    void printArray()
    {
        for (int i = 0; i < N; ++i)
        {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main()
{
    MyGenericClass<int> obj1(1); // explicit deduction
    std::cout << obj1.getData() << std::endl;

    MyGenericClass obj2("Hello"); // implicit deduction
    std::cout << obj2.getData() << std::endl;

    // MyGenericClass obj3; // error

    Array<int> intArray;
    Array<double, 10> doubleArray;
    intArray.printArray();
    doubleArray.printArray();

    return 0;
}