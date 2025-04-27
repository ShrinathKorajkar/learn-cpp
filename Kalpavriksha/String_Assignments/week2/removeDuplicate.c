#include <stdio.h>

/*
    Q: Remove Duplicate Characters from string.
    input: "characters"
    output: "charte"
*/

void removeDuplicateChar(char *str, char *result)
{
    int arr[150] = {0};
    while (*str != '\0')
    {
        int asciiEq = (int)*str;
        if (arr[asciiEq] == 0)
        {
            arr[asciiEq] = 1;
            *result++ = *str;
        }
        str++;
    }
    *result = '\0';
}

int main()
{
    char input[100];
    scanf("%s", input);
    char result[100];
    removeDuplicateChar(input, result);
    printf("String after removing duplicate characters : %s\n", result);
    return 0;
}