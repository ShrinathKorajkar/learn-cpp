#include <iostream>
#include <vector>
#include <algorithm>

void nextPermutation(std::vector<int> &arr)
{
    int n = arr.size();
    int pivot = -1;
    for (int i = n - 1; i > 0; i--)
    {
        if (arr[i] > arr[i - 1])
        {
            pivot = i - 1;
            break;
        }
    }

    if (pivot != -1)
    {
        int nextGreaterThanPivot = n - 1;
        for (int i = nextGreaterThanPivot; i > pivot; i--)
        {
            if (arr[i] > arr[pivot])
            {
                nextGreaterThanPivot = i;
                break;
            }
        }
        std::swap(arr[pivot], arr[nextGreaterThanPivot]);
    }

    std::reverse(arr.begin() + pivot + 1, arr.end());
}

int main()
{
    std::vector<int> arr = {5, 3, 6, 4, 3, 1};
    nextPermutation(arr);
    for (int a : arr)
    {
        std::cout << a << " ";
    }
    std::cout << std::endl;
    return 0;
}