#include <vector>
#include <algorithm>

using namespace std;

int maxArea(vector<int> &height)
{
    int maxArea = 0;
    int leftPointer = 0;
    int rightPointer = height.size() - 1;

    while (leftPointer < rightPointer)
    {
        int containerWidth = rightPointer - leftPointer;
        int containerHeight = std::min(height[leftPointer], height[rightPointer]);

        int currentArea = containerWidth * containerHeight;

        maxArea = std::max(maxArea, currentArea);

        if (height[leftPointer] < height[rightPointer])
        {
            leftPointer++;
        }
        else
        {
            rightPointer--;
        }
    }

    return maxArea;
}
