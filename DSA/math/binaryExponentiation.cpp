/*
    Binary Exponentiation
*/

double myPow(double x, int n)
{
    double result = 1;
    long binaryForm = n;

    if (x == 0 || x == 1)
    {
        return x;
    }

    if (x == -1)
    {
        if (n % 2 == 0)
        {
            return -x;
        }
        else
        {
            return x;
        }
    }

    if (binaryForm < 0)
    {
        x = 1 / x;
        binaryForm = -binaryForm;
    }

    while (binaryForm > 0)
    {
        if (binaryForm & 1)
        {
            result *= x;
        }
        x *= x;
        binaryForm = binaryForm / 2;
    }

    return result;
}