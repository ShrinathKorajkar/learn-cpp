#include <iostream>
#include <vector>

int findDuplicate(std::vector<int> &nums)
{
    int len = nums.size();
    std::vector<int> set(len, 0);
    for (auto num : nums)
    {
        set[num]++;
        if (set[num] == 2)
        {
            return num;
        }
    }
    return -1;
}

/*
*Using slow fast pointer
    arr = [3, 1, 3, 4, 2]
    ind = [0, 1, 2, 3, 4]

    linkedList = 0 -> 3 -> 4 -> 2 -> 3 (cycle in linked list)
*/
int findDuplicate(std::vector<int> &nums)
{
    int slow = nums[0];
    int fast = nums[0];

    do
    {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);

    slow = nums[0];

    while (slow != fast)
    {
        slow = nums[slow];
        fast = nums[fast];
    }
    return slow;
}

int main()
{
    return 0;
}