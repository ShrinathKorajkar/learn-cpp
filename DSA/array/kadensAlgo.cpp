#include <iostream>
/*
    maximum subarray sum
*/
int main()
{
    int arr[] = {3, -4, 7, 1, 2, -3, 5, -8};

    int maxSum = INT_MIN;
    int currSum = 0;
    for (int num : arr)
    {
        currSum += num;
        maxSum = std::max(maxSum, currSum);
        if (currSum < 0)
        {
            currSum = 0;
        }
    }

    std::cout << "Maximum subarray sum: " << maxSum << std::endl;

    return 0;
}