#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
    Caesar Cipher : Caesar Cipher technique is one of the earliest and simplest methods of encryption technique.
    each letter of a given text is replaced by a letter with a fixed number of positions down the alphabet.
    For example with a shift of 1, A would be replaced by B, B would become C, and so on.

    Q: Given a string and shift number, Output the cipher text
    input: str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"       shift = 23
    output: "XYZABCDEFGHIJKLMNOPQRSTUVW"
*/

void encrypt(char *text, int shift, char *cipher)
{
    int len = strlen(text);
    int i;
    for (i = 0; i < len; i++)
    {
        if (isupper(text[i]))
            cipher[i] = (char)((int)(text[i] + shift - 65) % 26 + 65);
        else
            cipher[i] = (char)((int)(text[i] + shift - 97) % 26 + 97);
    }
    cipher[i] = '\0';
}

int main()
{
    char text[] = "ATTACKATONCE";
    char cipher[100];
    int shift = 4;

    encrypt(text, shift, cipher);

    printf("Original text : %s\n", text);
    printf("Cipher text : %s\n", cipher);

    return 0;
}