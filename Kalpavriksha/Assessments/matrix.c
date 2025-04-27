/*
    Q1: Program to multiply matrix using pointers
    input: arr[m][n] = {{1, 1}, {2, 2}}
            arr2[n][p] = {{1, 1}, {2, 2}}
    output; result[m][n] = {{3, 3}, {6, 6}}
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void printMatrix(int **mat, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", *(*(mat + i) + j));
        }
        printf("\n");
    }
}

void takeInput(int **mat, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d ", (*(mat + i) + j));
        }
    }
}

int **createMatrix(int m, int n)
{
    int **mat = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
    {
        *(mat + i) = (int *)malloc(n * sizeof(int));
    }
    return mat;
}

void multiplyMatrix(int **res, int **mat1, int **mat2, int m, int n, int p)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < p; j++)
        {
            *(*(res + i) + j) = 0;
            for (int k = 0; k < n; k++)
            {
                *(*(res + i) + j) += (*(*(mat1 + i) + k)) * (*(*(mat2 + k) + j));
            }
        }
    }
}

void destroyMatrix(int **mat, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        free(*(mat + i));
    }
    free(mat);
}

int main()
{
    int m = 0, n = 0, p = 0;
    printf("Enter the size of matrix m, n, p: ");
    scanf("%d %d %d", &m, &n, &p);

    int **mat1 = createMatrix(m, n);
    int **mat2 = createMatrix(n, p);
    int **res = createMatrix(m, p);

    printf("\nEnter the matrix 1 of size %d * %d :\n", m, n);
    takeInput(mat1, m, n);

    printf("\nEnter the matrix 2 of size %d * %d : \n", n, p);
    takeInput(mat2, n, p);

    multiplyMatrix(res, mat1, mat2, m, n, p);

    printf("\nResultant Matrix of size %d * %d : \n", m, p);
    printMatrix(res, m, p);

    destroyMatrix(mat1, m, n);
    destroyMatrix(mat2, n, p);
    destroyMatrix(res, m, p);
    return 0;
}
