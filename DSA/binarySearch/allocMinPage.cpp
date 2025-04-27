#include <iostream>
#include <vector>
#include <algorithm>
/*
You are given an array arr[] of integers, where each element arr[i] represents the number of pages in the ith book. You
also have an integer k representing the number of students. The task is to allocate books to each student such that:

- Each student receives atleast one book.
- Each student is assigned a contiguous sequence of books.
- No book is assigned to more than one student.
- The objective is to minimize the maximum number of pages assigned to any student. In other words, out of all possible
  allocations, find the arrangement where the student who receives the most pages still has the smallest possible maximum.

Note: Return -1 if a valid assignment is not possible, and allotment should be in contiguous order
Input: arr[] = [12, 34, 67, 90], k = 2
Output: 113
Explanation: Allocation can be done in following ways:
[12] and [34, 67, 90] Maximum Pages = 191
[12, 34] and [67, 90] Maximum Pages = 157
[12, 34, 67] and [90] Maximum Pages = 113.
Therefore, the minimum of these cases is 113, which is selected as the output.
*/

bool allocateToStud(std::vector<int> &arr, int k, long long mid)
{
    int totalStudReq = 1;
    long long currSum = 0;
    for (int pages : arr)
    {
        if (pages > mid || totalStudReq > k)
        {
            return false;
        }
        currSum += pages;
        if (currSum > mid)
        {
            currSum = pages;
            totalStudReq++;
        }
    }
    return totalStudReq <= k;
}

int findPages(std::vector<int> &arr, int k)
{
    if (k > arr.size())
    {
        return -1;
    }

    long long start = *max_element(arr.begin(), arr.end());

    long long sum = 0;
    for (int num : arr)
    {
        sum += num;
    }

    long long end = sum;

    long long currentBest = -1;

    while (start <= end)
    {
        long long mid = start + (end - start) / 2;
        bool isPossible = allocateToStud(arr, k, mid);
        if (isPossible)
        {
            currentBest = mid;
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }

    return currentBest;
}

int main()
{
    std::vector<int> arr = {1, 2, 3, 4};
    int k = 2;
    std::cout << findPages(arr, k) << std::endl;
    return 0;
}