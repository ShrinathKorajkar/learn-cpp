#include <iostream>
#include <vector>
#include <map>

using namespace std;

/*
Dutch National Flag Algorithm
*/

void sortColors(vector<int> &nums)
{
    int red = 0;
    int white = 0;
    int blue = nums.size() - 1;
    while (white <= blue)
    {
        if (nums[white] == 0)
        {
            std::swap(nums[red], nums[white]);
            white++;
            red++;
        }
        else if (nums[white] == 2)
        {
            std::swap(nums[white], nums[blue]);
            blue--;
        }
        else
        {
            white++;
        }
    }
}

int main()
{

    return 0;
}