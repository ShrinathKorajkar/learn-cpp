#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/*
    Q:  Given a non-empty string s and an abbreviation abbr, return whether the string matches with the given abbreviation.
        An abbreviation is a shortened form of a word, represented by a number followed by a letter.
    Input: "internationalization"       abbr = "i12iz4n"
    Output: true.
*/

bool matchesAbbr(char *str, char *abbr)
{
    int lenStr = strlen(str);
    int lenAbbr = strlen(abbr);
    int i = 0, j = 0;

    while (i < lenStr && j < lenAbbr)
    {
        if (isdigit(abbr[j]))
        {
            int count = 0;
            while (j < lenAbbr && isdigit(abbr[j]))
            {
                count = count * 10 + (abbr[j] - '0');
                j++;
            }
            i += count;
        }
        else
        {
            if (str[i] != abbr[j])
            {
                return false;
            }
            i++;
            j++;
        }
    }

    return i == lenStr && j == lenAbbr;
}

int main()
{
    char input[] = "internationalization";
    char abbr[] = "i12iz4n";
    if (matchesAbbr(input, abbr))
    {
        printf("Abbreviation matches with String");
    }
    else
    {
        printf("Abbreviation do not matches with String");
    }
    return 0;
}