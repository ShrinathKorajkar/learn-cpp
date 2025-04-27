/*
    Q: You're given strings jewels representing the types of stones that are jewels,
       and stones representing the stones you have. Each character in stones is a type of stone
       you have. You want to know how many of the stones you have are also jewels.
    input  :-  jewels = "aA", stones = "aAAbbbb"
    output :-  3
*/

#include <iostream>
using namespace std;

int numJewelsInStones(string jewels, string stones)
{
    int characters[150] = {0};
    for (char c : stones)
    {
        characters[(int)c]++;
    }
    int sum = 0;
    for (char c : jewels)
    {
        sum += characters[(int)c];
    }
    return sum;
}

int main()
{
    string jewels = "aA";
    string stones = "aAAbbbb";
    cout << numJewelsInStones(jewels, stones) << endl;
    return 0;
}