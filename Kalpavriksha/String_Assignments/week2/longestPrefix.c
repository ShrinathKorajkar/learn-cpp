#include <stdio.h>
#include <string.h>

/*
    Q: Find the longest common prefix string amongst an array of strings.
    Input: ["flower","flow","flight"]
    Output: "fl"
*/

void substring(char *dest, char *source, int beg, int end)
{
    for (int i = beg; i < end; i++)
    {
        *dest++ = *(source + i);
    }
    *dest = '\0';
}

void longestCommonPrefix(char *input, char *output)
{
    char *token = strtok(input, ",");
    substring(output, token, 1, strlen(token) - 1);
    int end = 0;
    while (token != NULL)
    {
        substring(token, token, 1, strlen(token) - 1);
        int tokensize = strlen(token);
        int outputsize = strlen(output);
        for (int i = 0; i < tokensize && i < outputsize; i++)
        {
            end = i;
            if (output[i] != token[i])
            {
                break;
            }
        }
        output[end] = '\0';
        token = strtok(NULL, ",");
    }
}

int main()
{
    char input[100];
    scanf("[%[^]]", input);
    char output[100];
    longestCommonPrefix(input, output);
    printf("Longest Common Prefix : \"%s\"\n", output);
    return 0;
}