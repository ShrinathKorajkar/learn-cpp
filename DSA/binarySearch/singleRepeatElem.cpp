#include <iostream>
#include <vector>

int singleNonDuplicate(std::vector<int> &nums)
{
    int start = 1;
    int end = nums.size() - 2;

    if (nums.size() == 1)
    {
        return nums[0];
    }
    if (nums[0] != nums[1])
    {
        return nums[0];
    }
    if (nums[nums.size() - 1] != nums[nums.size() - 2])
    {
        return nums[nums.size() - 1];
    }

    while (start <= end)
    {
        int mid = start + (end - start) / 2;
        if (nums[mid - 1] != nums[mid] && nums[mid] != nums[mid + 1])
        {
            return nums[mid];
        }
        if (mid & 1)
        {
            if (nums[mid] == nums[mid + 1])
            {
                end = mid - 1;
            }
            else
            {
                start = mid + 1;
            }
        }
        else
        {
            if (nums[mid] == nums[mid + 1])
            {
                start = mid + 1;
            }
            else
            {
                end = mid - 1;
            }
        }
    }
    return -1;
}

int main()
{
    std::vector<int> nums = {1, 1, 2, 3, 3, 4, 4, 5, 5, 6, 6};
    std::cout << singleNonDuplicate(nums) << std::endl;

    return 0;
}
