#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
    A,  B,  C,  D ......  W,  X, Y, Z
    65, 66, 67, 68 ....  87, 88, 89 90

    Q: Program to print the mirror character of the given character.
    input: "AMNZamnz"
    output: "ZNMAznma"
*/

void findMirror(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (isupper(str[i]))
        {
            str[i] = 'Z' - str[i] + 'A';
        }
        else
        {
            str[i] = 'z' - str[i] + 'a';
        }
    }
}

int main()
{
    char str[20];
    printf("Enter String : ");
    scanf("%s", str);
    findMirror(str);
    printf("Mirror Characters : %s\n", str);
    return 0;
}