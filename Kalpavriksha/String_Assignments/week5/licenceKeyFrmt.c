#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
    Q:  You are given a license key represented as a string s that consists of only alphanumeric characters and dashes.
        The string is separated into n + 1 groups by n dashes. You are also given an integer k.
        We want to reformat the string s such that each group contains exactly k characters, except for the first group,
        which could be shorter than k but still must contain at least one character. Furthermore, there must be a dash
        inserted between two groups, and you should convert all lowercase letters to uppercase.

    Input: "2-5g-3-J"       K = 2                           Input2: s = "5F3Z-2e-9-w", k = 4
    Output: "2-5G-3J"                                       Output: "5F3Z-2E9W"
*/

char *formatLicenseKey(char *licenseKey, int k)
{
    int len = strlen(licenseKey);
    char *output = calloc(len + 1, sizeof(char));
    int i = 0, j = 0;
    while (licenseKey[i] != '-' && i < len)
    {
        output[j++] = toupper(licenseKey[i++]);
    }
    int keyLen = k;
    while (i < len)
    {
        if (licenseKey[i] == '-')
        {
            i++;
            continue;
        }
        if (keyLen == k)
        {
            output[j++] = '-';
            keyLen = 0;
        }
        output[j++] = toupper(licenseKey[i++]);
        keyLen++;
    }
    output[j] = '\0';
    return output;
}

int main()
{
    char licenseKey[] = "5F3Z-2e-9-w";
    int k = 4;
    char *output = formatLicenseKey(licenseKey, k);
    printf("Formatted License Key : %s\n", output);
    free(output);
    return 0;
}