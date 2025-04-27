/*
    Given an integer k. The task is to find the number of integers 1 < n < k,
    for which n and n + 1 have the same number of positive divisors
*/
#include "samePosDiv.h"

#include <iostream>

int main()
{
    /*
        Constraints
        1 <= T <= 10^6
        3 <= K <= 10^7
    */
    int testcases = 0;
    std::cin >> testcases;
    while (testcases-- > 0)
    {
        int k = 0;
        std::cin >> k;
        std::cout << sameAdjacentPositiveDivisors(k) << std::endl;
    }

    return 0;
}
