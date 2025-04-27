#include <stdio.h>
#include <string.h>

/*
    Q: Given a string, replace repeated characters with their count. If the compressed
    string is not shorter than the original string, return the original string.
    Input: "aabcccccaaa"
    Output: "a2b1c5a3"
*/

void compressString(char *inp, char *res)
{
    char current = inp[0];
    int count = 1;
    int len = strlen(inp);

    for (int i = 1; i < len; i++)
    {
        if (inp[i] == current)
        {
            count++;
        }
        else
        {
            *res++ = current;
            *res++ = '0' + count;
            current = inp[i];
            count = 1;
        }
    }
    *res++ = current;
    *res++ = '0' + count;
    *res = '\0';
}

int main()
{
    char inp[] = "aabcccccaaa";
    char res[20];
    compressString(inp, res);
    if (strlen(res) < strlen(inp))
    {
        printf("Compressed String : %s\n", res);
    }
    else
    {
        printf("String cannot be compressed");
    }
    return 0;
}
