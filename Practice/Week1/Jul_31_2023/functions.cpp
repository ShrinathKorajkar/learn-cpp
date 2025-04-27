/*
    Function signature, prototype, actual and formal parameters, definition
    default, call by value, ref, ommit para
*/
#include <iostream>
using namespace std;

int function1(int /*notUsed*/, int a, int *b, int c = 3)
{
    *b = a + c;
    a += c;
    return a;
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int &setValue(int i)
{
    return arr[i];
}

int count = 0;
int main()
{
    if (count < 2)
    {
        count++;
        cout << count << endl;
        main();
    }

    if (count == 2)
    {
        count++;
        int b = 3;
        int a = function1(1, 2, &b);
        cout << a << " " << b << endl;

        a = 2;
        b = 3;
        swap(a, b);
        cout << a << " " << b << endl;

        setValue(0) = 0;
        setValue(1) = 1;
        cout << arr[0] << " " << arr[1] << endl;
    }

    return 0;
}