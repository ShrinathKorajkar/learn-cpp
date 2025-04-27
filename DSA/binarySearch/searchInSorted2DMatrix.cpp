#include <iostream>
#include <vector>
/*
Matrix sorted in row and col wise such that every row is sorted and every col is sorted
*/

bool searchMatrix(std::vector<std::vector<int>> &matrix, int target)
{
    int totalRows = matrix.size();
    int totalCols = matrix[0].size();
    int start = 0;
    int end = totalCols - 1;
    while (start < totalRows && end > 0)
    {
        if (matrix[start][end] == target)
        {
            return true;
        }
        if (matrix[start][end] < target)
        {
            start++;
        }
        else
        {
            end--;
        }
    }
    return false;
}

int main()
{
    std::vector<std::vector<int>> matrix = {{1, 4, 7, 11, 15},
                                            {2, 5, 8, 12, 19},
                                            {3, 6, 9, 16, 22},
                                            {10, 13, 14, 17, 24},
                                            {18, 21, 23, 26, 30}};
    std::cout << searchMatrix(matrix, 5);
    return 0;
}