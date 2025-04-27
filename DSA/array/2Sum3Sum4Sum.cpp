#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>

std::vector<int> twoSum(std::vector<int> &arr, int sum)
{
    std::unordered_map<int, int> map;
    std::vector<int> ans;
    for (auto num : arr)
    {
        int diff = sum - num;
        if (map.find(diff) != map.end())
        {
            ans.push_back(diff);
            ans.push_back(map[diff]);
            break;
        }
        map[num] = diff;
    }
    return ans;
}

std::vector<std::vector<int>> threeSum1(std::vector<int> &nums)
{
    int n = nums.size();
    std::vector<std::vector<int>> ans;
    std::set<std::vector<int>> uniqueSet;

    for (int i = 0; i < n; i++)
    {
        int target = -nums[i];
        std::set<int> s;

        for (int j = i + 1; j < n; j++)
        {
            int third = target - nums[j];

            if (s.find(third) != s.end())
            {
                std::vector<int> triplets = {nums[i], nums[j], third};
                std::sort(triplets.begin(), triplets.end());
                uniqueSet.insert(triplets);
            }
            s.insert(third);
        }
    }

    ans.emplace_back(uniqueSet.begin(), uniqueSet.end());
    return ans;
}

std::vector<std::vector<int>> threeSum2(std::vector<int> &nums)
{
    int n = nums.size();
    std::vector<std::vector<int>> ans;
    std::sort(nums.begin(), nums.end());

    for (int i = 0; i < n; i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
        {
            continue;
        }
        int j = i + 1;
        int k = n - 1;
        while (j < k)
        {
            int sum = nums[i] + nums[j] + nums[k];
            if (sum < 0)
            {
                j++;
            }
            else if (sum > 0)
            {
                k--;
            }
            else
            {
                ans.push_back({nums[i], nums[j], nums[k]});
                j++;
                k--;
                while (j < k && nums[j] == nums[j - 1])
                {
                    j++;
                }
            }
        }
    }

    return ans;
}

int main()
{
    std::vector<int> arr = {-1, 0, 2, 1, -4};
    std::vector<int> ans = twoSum(arr, 0);

    for (auto num : ans)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}