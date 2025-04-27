#include "samePosDiv.h"

int countPositiveDivisors(int number)
{
    int divisorCount = 0;

    // Loop up to sqrt(number)
    for (int currentDivisor = 1; currentDivisor * currentDivisor <= number; currentDivisor++)
    {
        if (number % currentDivisor == 0)
        {
            // If it is a perfect square
            if (currentDivisor * currentDivisor == number)
            {
                divisorCount++;
            }
            else
            {
                divisorCount += 2;
            }
        }
    }

    return divisorCount;
}

void populateDivisorCounts(int divisorCounts[], int len)
{
    for (int i = 1; i < len; i++)
    {
        divisorCounts[i] = countPositiveDivisors(i);
    }
}

int countSameAdjacentPositiveDivisors(int divisorCounts[], int len)
{
    int totalCount = 0;

    for (int i = 1; i < len - 1; i++)
    {
        if (divisorCounts[i] == divisorCounts[i + 1])
        {
            totalCount++;
        }
    }

    return totalCount;
}

int sameAdjacentPositiveDivisors(int k)
{
    int result = 0;

    int divisorCountLen = k + 2; // 1 - k+1
    int divisorCounts[divisorCountLen] = {0};

    populateDivisorCounts(divisorCounts, divisorCountLen);
    result = countSameAdjacentPositiveDivisors(divisorCounts, divisorCountLen);

    return result;
}
