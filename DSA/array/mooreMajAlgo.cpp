#include <iostream>
#include <vector>

int majorityElement(std::vector<int> &nums)
{
    int majElem = 0;
    int count = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (count == 0)
        {
            majElem = nums[i];
        }

        if (nums[i] == majElem)
        {
            count++;
        }
        else
        {
            count--;
        }
    }
    return majElem;
}