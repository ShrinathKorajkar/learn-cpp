#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
    Q: Given a Sentence of title case. Print snake_case, PascalCase, camelCase format
    input: "This Is Test String"
    output: ----------- snake_case -----------
            this_is_test_string

            ----------- camelCase -----------
            thisIsTestString

            ----------- PascalCase -----------
            ThisIsTestString
*/

void printSnakeCase(char *input, int len)
{
    printf("\n----------- snake_case -----------\n");
    for (int i = 0; i < len; i++)
    {
        if (input[i] == ' ')
        {
            printf("_");
            continue;
        }
        printf("%c", tolower(input[i]));
    }
    printf("\n");
}

void printCamelCase(char *input, int len)
{
    printf("\n----------- camelCase -----------\n");
    for (int i = 0; i < len; i++)
    {
        if (i == 0)
        {
            printf("%c", tolower(input[i]));
            continue;
        }
        if (input[i] == ' ')
        {
            continue;
        }
        printf("%c", input[i]);
    }
    printf("\n");
}

void printPascalCase(char *input, int len)
{
    printf("\n----------- PascalCase -----------\n");
    for (int i = 0; i < len; i++)
    {
        if (input[i] == ' ')
        {
            continue;
        }
        printf("%c", input[i]);
    }
    printf("\n");
}

int main()
{
    char inp[] = "This Is Test String";
    int len = strlen(inp);
    printSnakeCase(inp, len);
    printCamelCase(inp, len);
    printPascalCase(inp, len);
    return 0;
}