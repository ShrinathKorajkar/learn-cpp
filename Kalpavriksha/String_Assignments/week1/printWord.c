#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    Given a sentence, , print each word of the sentence in a new line.
    input : Learning C is fun
    Output: Learning
            C
            is
            fun
*/

int main()
{
    char *s;
    s = malloc(1024 * sizeof(char));
    scanf("%[^\n]", s);
    s = realloc(s, strlen(s) + 1);
    char *token = strtok(s, " ");
    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }
    free(s);
    return 0;
}