#include <stdio.h>
#include <string.h>

/*
    Q: 1. Find substring given start and end index
    input: str = "how are you doing"        start = 0       end = 12
    output: "how are you"

    2. Find substring given starting and ending character
    input: str = "how are you doing"        start = h       end = u
    output: "how are you"
*/

void substring(char *dest, char *source, int beg, int end)
{
    for (int i = beg; i < end; i++)
    {
        *dest++ = *(source + i);
    }
    *dest = '\0';
}

void substring2(char *dest, char *source, char beg, char end)
{
    while (beg != *source)
    {
        source++;
    }
    *dest++ = *source++;
    while (end != *source)
    {
        *dest++ = *source++;
    }
    *dest++ = *source;
    *dest = '\0';
}

int main()
{
    char str[] = "how are you doing";
    char dest[25], dest2[25];
    substring(dest, str, 0, 12);
    substring2(dest2, str, 'h', 'u');
    printf("%s\n", dest);
    printf("%s\n", dest2);
    return 0;
}