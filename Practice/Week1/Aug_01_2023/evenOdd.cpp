/*
    Q: Given array containing no of weapons each i soldier is holding. print ready for war if no of soldiers
       holding the even no of weapons is strictly more than odd no of weapon soldiers
    input  :-  arr[] = {1, 2, 4, 2, 1}
    output :-  READY FOR BATTLE
*/

#include <iostream>
using namespace std;

int main()
{
    int N;
    cin >> N;

    int *arr = new int[N];
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    int evenCount = 0, oddCount = 0;
    for (int i = 0; i < N; i++)
    {
        if (arr[i] % 2 == 0)
        {
            evenCount++;
        }
        else
        {
            oddCount++;
        }
    }

    if (evenCount > oddCount)
    {
        cout << "READY FOR BATTLE" << endl;
    }
    else
    {
        cout << "NOT READY" << endl;
    }

    delete arr;
    return 0;
}
