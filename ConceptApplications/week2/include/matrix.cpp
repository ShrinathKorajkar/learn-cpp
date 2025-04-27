#include <iostream>
#include "matrix.hpp"

namespace mat
{

    int **createMatrix(int totalRows, const int &totalCols)
    {
        int **matrix = new int *[totalRows];
        for (int row = 0; row < totalRows; row++)
        {
            *(matrix + row) = new int[totalCols];
        }
        return matrix;
    }

    void printMatrix(int **&mat, const int &totalRows, const int &totalCols)
    {
        for (int row = 0; row < totalRows; row++)
        {
            for (int col = 0; col < totalCols; col++)
            {
                std::cout << *(*(mat + row) + col) << " ";
            }
            std::cout << std::endl;
        }
    }

    void addMatrices(int **&res, int **&mat1, int **&mat2, const int &totalRows, const int &totalCols)
    {
        for (int row = 0; row < totalRows; row++)
        {
            for (int col = 0; col < totalCols; col++)
            {
                (*(*(res + row) + col)) = *(*(mat1 + row) + col) + *(*(mat2 + row) + col);
            }
        }
    }

    void multiplyMatrices(int **&res, int **&mat1, int **&mat2, const int &totalRows, const int &totalCommonRowCols, const int &totalCols)
    {
        for (int row = 0; row < totalRows; row++)
        {
            for (int col = 0; col < totalCols; col++)
            {
                *(*(res + row) + col) = 0;
                for (int commonRowCol = 0; commonRowCol < totalCommonRowCols; commonRowCol++)
                {
                    *(*(res + row) + col) += (*(*(mat1 + row) + commonRowCol)) * (*(*(mat2 + commonRowCol) + col));
                }
            }
        }
    }

    void deleteMatrix(int **&mat, const int &totalRows)
    {
        for (int row = 0; row < totalRows; row++)
        {
            delete[] *(mat + row);
        }
        delete[] mat;
        mat = nullptr;
    }

}