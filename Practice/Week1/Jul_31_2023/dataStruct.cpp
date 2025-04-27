#include <iostream>
using namespace std;

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int *p = arr;
    int len = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < len; i++)
    {
        cout << *(p + i) << " ";
    }
    cout << "\nhello" << endl;
    return 0;
}
