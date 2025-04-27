#include <iostream>
#include <vector>
using namespace std;

vector<int> productExceptSelf(vector<int> &nums)
{
    int len = nums.size();
    vector<int> ans(len, 1);

    for (int i = 1; i < len; i++)
    {
        ans[i] = ans[i - 1] * nums[i - 1];
    }

    int suffix = 1;
    for (int i = len - 2; i >= 0; i--)
    {
        suffix *= nums[i + 1];
        ans[i] *= suffix;
    }

    return ans;
}
