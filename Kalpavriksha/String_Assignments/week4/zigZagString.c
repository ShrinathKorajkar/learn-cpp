#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    Q: Given a string and a number of rows, convert the string into a zigzag pattern and read it line by line.
    Input: "ABCDEFGHIJKLMN"         rows = 3
    ZigZagPattern:
            A   E   I   M
            B D F H J L N
            C   G   K
    Output: "AEIMBDFHJLNCGK"
*/

char **initPattern(int rows, int cols)
{
    char **zigZagPattern = calloc((rows), sizeof(char));
    for (int i = 0; i < rows; i++)
    {
        zigZagPattern[i] = calloc((cols), sizeof(char));
    }
    return zigZagPattern;
}

void freePattern(char **zigZagPattern, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(zigZagPattern[i]);
    }
    free(zigZagPattern);
}

char **fillPattern(char **zigZagPattern, int rows, char *inp, int len)
{
    int i = 0, count = 0;
    int *index = calloc(rows, sizeof(int));
    while (i < len)
    {
        for (count = 0; count < rows; count++)
        {
            zigZagPattern[count][index[count]] = inp[i++];
            index[count]++;
        }
        for (count = rows - 2; count > 0; count--)
        {
            zigZagPattern[count][index[count]] = inp[i++];
            index[count]++;
        }
    }
    free(index);
    return zigZagPattern;
}

char *convertIntoString(char **zigZagPattern, int rows, int len)
{
    char *result = calloc((len + 1), sizeof(char));
    int count = 0;
    for (int i = 0; i < rows; i++)
    {
        char *row = zigZagPattern[i];
        int rowLen = strlen(row);
        for (int j = 0; j < rowLen; j++)
        {
            result[count++] = row[j];
        }
    }
    return result;
}

char *zigZagPattern(char *inp, int rows)
{
    int len = strlen(inp);
    char **zigZagPattern = initPattern(rows, len + 1);

    zigZagPattern = fillPattern(zigZagPattern, rows, inp, len);

    char *result = convertIntoString(zigZagPattern, rows, len);

    freePattern(zigZagPattern, rows);

    return result;
}

int main()
{
    char inp[] = "ABCDEFGHIJKLMN";
    int rows = 3;
    char *result = zigZagPattern(inp, rows);
    printf("%s \n", result);
    free(result);
    return 0;
}