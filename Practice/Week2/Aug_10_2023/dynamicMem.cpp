#include <iostream>

int *createDynamicArray(int size)
{
    int *dynamicArray = new int[size];
    return dynamicArray;
}

void modifyArray(int *&array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        array[i] *= 2;
    }
}

void dynamicArray()
{
    const int size = 5;
    int *dynamicArray = createDynamicArray(size);

    for (int i = 0; i < size; ++i)
    {
        dynamicArray[i] = i + 1;
    }

    modifyArray(dynamicArray, size);

    for (int i = 0; i < size; ++i)
    {
        std::cout << dynamicArray[i] << " ";
    }
    std::cout << std::endl;

    delete[] dynamicArray;
}

void pointerException()
{
    try
    {
        int *p = new int[10000000000];
        p[0] = 0;
        delete[] p;
    }
    catch (std::bad_alloc &ex)
    {
        std::cout << ex.what() << std::endl;
        std::cout << "Cannot allocate memory" << std::endl;
    }

    // another
    int *ptr = new (std::nothrow) int[10000000000];
    if (ptr == nullptr)
    {
        std::cout << "Cannot allocate memory" << std::endl;
    }
}

int main()
{
    // dynamicArray();

    // pointerException();

    int x = 20;
    void *ptr = &x;
    // ptr++; // error

    int *intPtr = static_cast<int *>(ptr);
    intPtr++;

    return 0;
}
