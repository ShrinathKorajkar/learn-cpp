#include <stdio.h>
#include <string.h>

/*
    Q: Given roman number, Convert Roman numbers to Decimal
    Input: IX
    Output: 9

      SYMBOL    VALUE
        I         1
        IV        4
        V         5
        IX        9
        X         10
        XL        40
        L         50
        XC        90
        C         100
        CD        400
        D         500
        CM        900
        M         1000
*/

int value(char r)
{
    if (r == 'I')
        return 1;
    if (r == 'V')
        return 5;
    if (r == 'X')
        return 10;
    if (r == 'L')
        return 50;
    if (r == 'C')
        return 100;
    if (r == 'D')
        return 500;
    if (r == 'M')
        return 1000;

    return -1;
}

int romanToDecimal(char str[])
{
    int res = 0, len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        int s1 = value(str[i]);

        if (i + 1 < len)
        {
            int s2 = value(str[i + 1]);
            if (s1 >= s2)
            {
                res += s1;
            }
            else
            {
                res += s2 - s1;
                i++;
            }
        }
        else
        {
            res = res + s1;
        }
    }
    return res;
}

int main()
{
    char str[10] = "MCMIV";
    printf("Roman : %s  => Integer : %d\n", str, romanToDecimal(str));
    return 0;
}