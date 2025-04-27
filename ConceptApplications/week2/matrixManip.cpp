#include <iostream>
#include "include/matrix.hpp"

void printError(const char *message)
{
    std::cout << "\n\n"
              << message
              << "\n\n";
    std::cin.clear();
    std::cin.ignore();
}

void readMatrix(int **&mat, const int &totalRows, const int &totalCols)
{
    for (int row = 0; row < totalRows; row++)
    {
        for (int col = 0; col < totalCols; col++)
        {
            std::cin >> *(*(mat + row) + col);
            if (std::cin.fail())
            {
                printError("INVALID INPUT!... Enter Numbers");
                std::cout << "Enter Once Again : \n";
                readMatrix(mat, totalRows, totalCols);
            }
        }
    }
}

int **createNReadMatrix(const int &totalRows, const int &totalCols)
{
    int **matrix = mat::createMatrix(totalRows, totalCols);
    readMatrix(matrix, totalRows, totalCols);
    return matrix;
}

void performAddition()
{
    int totalRows = 0, totalCols = 0;
    std::cout << "\nEnter the size of Matrices m x n : ";
    std::cin >> totalRows >> totalCols;
    if (std::cin.fail())
    {
        printError("INVALID INPUT!... Enter Numbers");
        performAddition();
    }
    else
    {
        std::cout << "\nEnter Matrix 1 of Size " << totalRows << " x " << totalCols << std::endl;
        int **matrix1 = createNReadMatrix(totalRows, totalCols);

        std::cout << "\nEnter Matrix 2 of Size " << totalRows << " x " << totalCols << std::endl;
        int **matrix2 = createNReadMatrix(totalRows, totalCols);

        int **resultMatrix = mat::createMatrix(totalRows, totalCols);
        mat::addMatrices(resultMatrix, matrix1, matrix2, totalRows, totalCols);

        std::cout << "\nResultant Matrix After Addition : " << std::endl;
        mat::printMatrix(resultMatrix, totalRows, totalCols);

        mat::deleteMatrix(matrix1, totalRows);
        mat::deleteMatrix(matrix2, totalRows);
        mat::deleteMatrix(resultMatrix, totalRows);
    }
}

void performMultiplication()
{
    int totalRowsOfMat1 = 0;
    int commonRowCol = 0;
    int totalColsOfMat2 = 0;
    std::cout << "\nEnter the size of Matrices m, n, p where matrix are of size m x n, n x p : ";
    std::cin >> totalRowsOfMat1 >> commonRowCol >> totalColsOfMat2;
    if (std::cin.fail())
    {
        printError("INVALID INPUT!... Enter Numbers");
        performMultiplication();
    }
    else
    {
        std::cout << "\nEnter Matrix 1 of Size " << totalRowsOfMat1 << " x " << commonRowCol << std::endl;
        int **matrix1 = createNReadMatrix(totalRowsOfMat1, commonRowCol);

        std::cout << "\nEnter Matrix 2 of Size " << commonRowCol << " x " << totalColsOfMat2 << std::endl;
        int **matrix2 = createNReadMatrix(commonRowCol, totalColsOfMat2);

        int **resultMatrix = mat::createMatrix(totalRowsOfMat1, totalColsOfMat2);
        mat::multiplyMatrices(resultMatrix, matrix1, matrix2, totalRowsOfMat1, commonRowCol, totalColsOfMat2);

        std::cout << "\nResultant Matrix After Multiplication : " << std::endl;
        mat::printMatrix(resultMatrix, totalRowsOfMat1, totalColsOfMat2);

        mat::deleteMatrix(matrix1, totalRowsOfMat1);
        mat::deleteMatrix(matrix2, commonRowCol);
        mat::deleteMatrix(resultMatrix, totalRowsOfMat1);
    }
}

int main()
{
    bool runInfiniteLoop = true;
    while (runInfiniteLoop)
    {
        int choice = 0;
        std::cout << "\n\n\n-------Choose The Operation to be Performed-------\n";
        std::cout << "\n1. Add Matrices    2. Multiply Matrices    3. EXIT\n";
        std::cout << "\nYour Choice : 1 / 2 / 3 ? : ";
        std::cin >> choice;
        if (std::cin.fail())
        {
            printError("INVALID INPUT!... Enter Numbers");
            continue;
        }
        switch (choice)
        {
        case 1:
            performAddition();
            break;
        case 2:
            performMultiplication();
            break;
        case 3:
            runInfiniteLoop = false;
            break;
        default:
            std::cout << "Invalid Choice !.. Please Type 1, 2, or 3";
        }
    }

    return 0;
}
