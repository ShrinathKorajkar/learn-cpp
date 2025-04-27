#include <iostream>

/*
    Q: To print Pattern of give size
    input : 13
    output:
        1                       1
        1 0                   1 0
        1 0 1               1 0 1
        1 0 1 0           1 0 1 0
        1 0 1 0 1       1 0 1 0 1
        1 0 1 0 1 0   1 0 1 0 1 0
        1 0 1 0 1 0 1 0 1 0 1 0 1
        1 0 1 0 1 0   1 0 1 0 1 0
        1 0 1 0 1       1 0 1 0 1
        1 0 1 0           1 0 1 0
        1 0 1               1 0 1
        1 0                   1 0
        1                       1
*/

void printPattern(int patternSize)
{
    int count = 1;
    int mid = (patternSize + 1) / 2;
    int printUpperPattern = 1;

    int i = 0, j = 0;
    for (i = 0; i < patternSize; i++)
    {
        int toPrint = 1;
        for (j = 0; j < patternSize; j++)
        {
            if (j < count || j >= patternSize - count)
            {
                std::cout << toPrint << " ";
                toPrint = toPrint == 1 ? 0 : 1;
            }
            else
            {
                std::cout << "  ";
                toPrint = 1;
            }
        }
        std::cout << std::endl;

        if (printUpperPattern)
        {
            count++;
            if (count > mid)
            {
                printUpperPattern = 0;
                count = patternSize % 2 == 0 ? mid : mid - 1;
            }
        }
        else
        {
            count--;
        }
    }
}

int main()
{
    int patternSize = 0;
    std::cout << "Enter the size of Pattern : ";
    std::cin >> patternSize;

    printPattern(patternSize);
    return 0;
}