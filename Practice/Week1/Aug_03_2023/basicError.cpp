#include <iostream>
using namespace std;

// Syntax  :-  {,;:><

int logicError(int a, int b)
{
    return a + b * b; // has to be (a + b) * b
}

int nullPtrDereference()
{
    int *p = nullptr;
    return *p;
}

void memoryLeak()
{
    int *arr = new int[10];
}

void arrayBoundExp()
{
    int arr[] = {1, 2};
    cout << arr[3] << endl;
}

int main()
{
    return 0;
}