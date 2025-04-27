#include <iostream>
#include <vector>
#include <algorithm>

bool isPossible(std::vector<int> stalls, int noOfCows, int minDistance)
{
    int cowsPlaced = 1;
    int lastPosition = stalls[0];
    for (int i = 1; i < stalls.size(); i++)
    {
        if (cowsPlaced == noOfCows)
        {
            return true;
        }
        if (stalls[i] - lastPosition >= minDistance)
        {
            cowsPlaced++;
            lastPosition = stalls[i];
        }
    }
    return false;
}

int maxDistance(std::vector<int> stalls, int noOfCows)
{
    int n = stalls.size();
    std::sort(stalls.begin(), stalls.end());

    int minDistance = 1;
    int maxDistance = stalls[n - 1] - stalls[0];
    int answer = -1;
    while (minDistance <= maxDistance)
    {
        int mid = minDistance + (maxDistance - minDistance) / 2;
        if (isPossible(stalls, noOfCows, mid))
        {
            minDistance = mid + 1;
            answer = mid;
        }
        else
        {
            maxDistance = mid - 1;
        }
    }
    return answer;
}

int main()
{
    std::vector<int> stalls = {1, 2, 8, 4, 9};
    std::cout << maxDistance(stalls, 3) << std::endl;

    return 0;
}