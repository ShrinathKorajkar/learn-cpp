#include <iostream>

/*
Euclid's Algo
LCM

    a * b = gcd(a, b) * lcm(a, b)
*/

int greatestCommonDivisor(int a, int b)
{
    if (b == 0)
    {
        return a;
    }

    return greatestCommonDivisor(b, a % b);
    // return greatestCommonDivisor(b, a - b);
}

int lcm(int a, int b)
{
    int gcd = greatestCommonDivisor(a, b);
    return (a * b) / gcd;
}

int main()
{
    std::cout << greatestCommonDivisor(24, 88) << std::endl;
    return 0;
}