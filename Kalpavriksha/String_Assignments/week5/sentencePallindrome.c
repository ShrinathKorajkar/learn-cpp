#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

/*
    Q: Given a string, determine if it is a valid Palindrome. Consider alphanumeric characters and ignore cases.
    Input: "A man, a plan, a canal: Panama"
    Output: "valid Palindrome"
*/

char *alphaNumericString(char *input, int len)
{
    char *result = malloc(len * sizeof(char));
    int j = 0;
    for (int i = 0; i < len; i++)
    {
        if ((input[i] >= '0' && input[i] <= '9') || (input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
        {
            result[j++] = tolower(input[i]);
        }
    }
    result[j] = '\0';
    return result;
}

bool checkPalindrome(char *input)
{
    bool isPalindrome = true;
    int len = strlen(input);
    char *modifiedString = alphaNumericString(input, len);

    int len2 = strlen(modifiedString);
    for (int i = 0, j = len2 - 1; i < len2 / 2; i++, j--)
    {
        if (modifiedString[i] != modifiedString[j])
        {
            isPalindrome = false;
            break;
        }
    }
    free(modifiedString);
    return isPalindrome;
}

int main()
{
    char input[] = "A man, a plan, a canal: Panama";
    if (checkPalindrome(input))
    {
        printf("valid Palindrome");
    }
    else
    {
        printf("Not a Palindrome");
    }
    return 0;
}