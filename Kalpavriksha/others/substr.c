#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool searchString(const char *haystack, const char *needle)
{
    char *result = strstr(haystack, needle);
    if (result == NULL)
    {
        return false;
    }
    return true;
}

void substring(char *dest, char *source, int beg, int end)
{
    for (int i = beg; i < end; i++)
    {
        *dest++ = *(source + i);
    }
    *dest = '\0';
}

char *substringByIndex(const char *str, int start, int end) {
    int length = end - start + 1;
    char *substring = (char *)malloc(length + 1);
    strncpy(substring, str + start, length);
    substring[length] = '\0';
    return substring;
}

char *substringByLength(const char *str, int start, int length) {
    char *substring = (char *)malloc(length + 1);
    strncpy(substring, str + start, length);
    substring[length] = '\0';
    return substring;
}

char *substringUntilDelimiter(const char *str, char delimiter) {
    int length = 0;
    const char *ptr = str;

    while (*ptr != delimiter && *ptr != '\0') {
        length++;
        ptr++;
    }

    char *substring = (char *)malloc(length + 1);
    strncpy(substring, str, length);
    substring[length] = '\0';
    return substring;
}

char *substringAfterDelimiter(const char *str, char delimiter) {
    const char *ptr = strchr(str, delimiter);
    if (ptr == NULL) {
        return NULL;
    }
    return strdup(ptr + 1);
}

int main() {
    const char *str = "Hello, World!";
    char *substring1 = substringByIndex(str, 7, 11);
    printf("Substring 1: %s\n", substring1);
    free(substring1);

    char *substring2 = substringByLength(str, 7, 5);
    printf("Substring 2: %s\n", substring2);
    free(substring2);

    char *substring3 = substringUntilDelimiter(str, ',');
    printf("Substring 3: %s\n", substring3);
    free(substring3);

    char *substring4 = substringAfterDelimiter(str, ',');
    printf("Substring 4: %s\n", substring4);
    free(substring4);

    return 0;
}
