#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
    Q: Check if two strings are anagram of each other(contain same chars)
    Input: str1 = "listen"      str2 = "silent"
    Output: "Anagram"
*/

#define NO_OF_CHARS 256

bool areAnagram(char *str1, char *str2)
{
    int count[NO_OF_CHARS] = {0};
    int i;
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 != len2)
    {
        return false;
    }

    for (i = 0; str1[i] && str2[i]; i++)
    {
        count[str1[i] - '0']++;
        count[str2[i] - '0']--;
    }

    for (i = 0; i < NO_OF_CHARS; i++)
    {
        if (count[i])
            return false;
    }

    return true;
}

int main()
{
    char str1[] = "listen";
    char str2[] = "silent";

    if (areAnagram(str1, str2))
    {
        printf("Anagram");
    }
    else
    {
        printf("Not Anagram");
    }

    return 0;
}
