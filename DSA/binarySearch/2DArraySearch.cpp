#include <iostream>
#include <vector>

int findCorrectRow(std::vector<std::vector<int>> &matrix, int target)
{
    int start = 0;
    int end = matrix.size() - 1;
    while (start <= end)
    {
        int mid = start + (end - start) / 2;
        if (matrix[mid][0] <= target && target <= matrix[mid][matrix[0].size() - 1])
        {
            return mid;
        }
        if (matrix[mid][0] > target)
        {
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }

    return -1;
}

bool searchMatrix(std::vector<std::vector<int>> &matrix, int target)
{
    int correctRow = findCorrectRow(matrix, target);

    if (correctRow == -1)
    {
        return false;
    }

    int startCol = 0;
    int endCol = matrix[0].size() - 1;
    while (startCol <= endCol)
    {
        int mid = (endCol - startCol) / 2 + startCol;
        if (matrix[correctRow][mid] == target)
        {
            return true;
        }
        if (matrix[correctRow][mid] < target)
        {
            startCol = mid + 1;
        }
        else
        {
            endCol = mid - 1;
        }
    }

    return false;
}

int main()
{
    std::vector<std::vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    std::cout << searchMatrix(matrix, 1) << std::endl;
    std::cout << searchMatrix(matrix, 7) << std::endl;
    std::cout << searchMatrix(matrix, 11) << std::endl;
    std::cout << searchMatrix(matrix, 16) << std::endl;
    std::cout << searchMatrix(matrix, 60) << std::endl;
    std::cout << searchMatrix(matrix, 23) << std::endl;
    std::cout << searchMatrix(matrix, 10) << std::endl;
    std::cout << searchMatrix(matrix, 20) << std::endl;
    std::cout << searchMatrix(matrix, 34) << std::endl;
    std::cout << searchMatrix(matrix, 3) << std::endl;
    std::cout << searchMatrix(matrix, 61) << std::endl;
    std::cout << searchMatrix(matrix, 0) << std::endl;

    return 0;
}