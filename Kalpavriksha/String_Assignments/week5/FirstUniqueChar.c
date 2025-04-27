#include <stdio.h>
#include <string.h>

/*
    Q: Given a string, find the first non-repeating character in it and return its index. If it doesn't exist, return -1.
    Input: "INTIMETEC"
    Output: 2
*/
int firstNonRepeatingCharacter(const char *input)
{
    int charMap[256] = {0};
    int indexFound = -1;
    int len = strlen(input);
    for (int i = 0; i < len; i++)
    {
        charMap[(int)input[i]]++;
    }
    for (int i = 0; i < len; i++)
    {
        if (charMap[(int)input[i]] == 1)
        {
            indexFound = i + 1;
            break;
        }
    }
    return indexFound;
}

int main()
{
    char input[] = "INTIMETEC";
    int index = firstNonRepeatingCharacter(input);
    if (index == -1)
    {
        printf("Non Repeating Character Doesn't exist");
    }
    else
    {
        printf("First Non Repeating Character %c Found at index %d\n", input[index], index);
    }
    return 0;
}