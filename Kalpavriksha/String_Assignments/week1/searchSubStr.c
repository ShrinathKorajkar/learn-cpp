#include <stdio.h>
#include <string.h>

/*
    Q: Search if given substring is present in the string
    input : str = "This is a test string"       str2 = "test"
    output: found at index : 10
*/
int findSubString(char *str, char *search)
{
    int found = -1;
    int len = strlen(str);
    int len2 = strlen(search);
    for (int i = 0; i < len; i++)
    {
        if (str[i] == *search)
        {
            int j = 0;
            for (; j < len2; j++)
            {
                if (str[i + j] != search[j])
                {
                    break;
                }
            }
            if (j == len2)
            {
                found = i;
                return found;
            }
        }
    }
    return found;
}

int searchString(const char *haystack, const char *needle)
{
    char *result = strstr(haystack, needle);

    if (result != NULL)
    {
        return result - haystack;
    }
    else
    {
        return -1;
    }
}

int main()
{
    char inp[] = "This is a test string";
    char search[] = "test";
    int found = findSubString(inp, search);
    if (found == -1)
    {
        printf("Not found\n");
    }
    else
    {
        printf("Found at index %d\n", found);
    }
}