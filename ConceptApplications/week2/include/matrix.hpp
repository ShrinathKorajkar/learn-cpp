#ifndef MATRIX_H
#define MATRIX_H

namespace mat
{
    int **createMatrix(int totalRows, const int &totalCols);

    void printMatrix(int **&mat, const int &totalRows, const int &totalCols);

    void addMatrices(int **&res, int **&mat1, int **&mat2, const int &totalRows, const int &totalCols);

    void multiplyMatrices(int **&res, int **&mat1, int **&mat2, const int &totalRows, const int &totalCommonRowCols, const int &totalCols);

    void deleteMatrix(int **&mat, const int &totalRows);
}

#endif