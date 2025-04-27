#include <iostream>
#include <vector>

int peakIndexInMountainArray(std::vector<int> &arr)
{
    int start = 1;
    int end = arr.size() - 2;
    while (start <= end)
    {
        int mid = start + (end - start) / 2;
        if (arr[mid - 1] < arr[mid] && arr[mid] > arr[mid + 1])
        {
            return mid;
        }
        if (arr[mid - 1] < arr[mid])
        {
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }
    return -1;
}

int main()
{
    std::vector<int> arr = {0, 1, 3, 2, 0};
    std::cout << arr[peakIndexInMountainArray(arr)] << std::endl;

    return 0;
}