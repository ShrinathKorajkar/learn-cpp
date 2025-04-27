#include <iostream>
#include <vector>
using namespace std;

vector<int> findMissingAndRepeatedValues(vector<vector<int>> &grid)
{
    int gridLen = grid.size();
    vector<int> ans(2);
    vector<int> numCame((gridLen * gridLen) + 1, 0);

    for (vector<int> row : grid)
    {
        for (int value : row)
        {
            numCame[value]++;
        }
    }
    for (int i = 1; i < (gridLen * gridLen) + 1; i++)
    {
        if (numCame[i] == 0)
        {
            ans[1] = i;
        }
        if (numCame[i] == 2)
        {
            ans[0] = i;
        }
    }
    return ans;
}

/*
    Alternate O(1) space:

    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        long long sum = 0, sqrSum = 0, n = grid.size(), N = n*n;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                sum += grid[i][j];
                sqrSum += grid[i][j] * grid[i][j];
            }
        }
        long long c1 = sum - (N * (N + 1)/2),  c2 = sqrSum - N*(N+1)*(2*N + 1)/6;
        return {(int)(c2/c1 + c1)/2, (int)(c2/c1 - c1)/2};
    }

    Using hashmap:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
    unordered_map<int, int> freq;
    for(int i = 0; i < grid.size(); ++i){
        for(int j = 0; j < grid.size(); ++j){
            freq[grid[i][j]]++;
        }
    }
    int repeat = 0, miss = 0, n = grid.size() * grid.size();
    for(int i = 1; i <= n; ++i){
        if(freq[i] == 2) repeat = i;
        if(freq[i] == 0) miss = i;
    }
    return {repeat, miss};
}
*/

int main()
{
    vector<vector<int>> grid = {{9, 1, 7}, {8, 9, 2}, {3, 4, 6}};
    vector<int> missingAndRepeated = findMissingAndRepeatedValues(grid);
    return 0;
}