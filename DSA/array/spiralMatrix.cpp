#include <iostream>
#include <vector>

void printSpiralMatrix(const std::vector<std::vector<int>> &matrix)
{
    int firstRow = 0;
    int lastRow = matrix.size() - 1;
    int firstCol = 0;
    int lastCol = matrix[0].size() - 1;

    while (firstRow <= lastRow && firstCol <= lastCol)
    {
        for (int i = firstCol; i < lastCol; i++)
        {
            std::cout << matrix[firstRow][i] << " ";
        }

        for (int i = firstRow; i < lastRow; i++)
        {
            std::cout << matrix[i][lastCol] << " ";
        }

        for (int i = lastCol; i > firstCol; i--)
        {
            std::cout << matrix[lastRow][i] << " ";
        }

        for (int i = lastRow; i > firstRow; i--)
        {
            std::cout << matrix[i][firstCol] << " ";
        }

        firstRow++;
        lastRow--;
        firstCol++;
        lastCol--;
    }
}

int main()
{
    std::vector<std::vector<int>> matrix = {{1, 2, 3, 4},
                                            {5, 6, 7, 8},
                                            {9, 10, 11, 12},
                                            {13, 14, 15, 16}};

    printSpiralMatrix(matrix);
    return 0;
}