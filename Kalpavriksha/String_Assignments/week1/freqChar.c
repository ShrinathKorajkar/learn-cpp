#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    Q: Given a string, , consisting of alphabets and digits, find the frequency of each digit in the given string.
    input: a11472o5t6
    output: 0 2 1 0 1 1 1 1 0 0
*/

int main()
{
    char *str;
    str = malloc(1024 * sizeof(char));
    scanf("%[^\n]", str);
    int len = strlen(str);
    str = realloc(str, len + 1);
    int arr[10] = {0};
    for (int i = 0; i < len; i++)
    {
        int ch = (int)(str[i] - '0');
        if (ch > -1 && ch < 10)
        {
            arr[ch]++;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    free(str);
    return 0;
}
