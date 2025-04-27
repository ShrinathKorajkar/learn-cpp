#include <iostream>
#include <vector>

/*
    program to find p and q such that p * q <= n.
    given n > 4, q > 1;
*/

void findPrimeNumbersInRange(bool *primeNumbers, const int &size)
{
    primeNumbers[0] = false;
    primeNumbers[1] = false;
    for (int i = 2; i * i <= size; i++)
    {
        primeNumbers[i] = true;
        for (int j = i * i; j <= size; j += i)
        {
            primeNumbers[j] = false;
        }
    }
}

void findPairOfPrimeNumbers(const std::vector<int> &primeNumbers, const int &nValue)
{
    int length = primeNumbers.size();
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (primeNumbers[i] * primeNumbers[j] <= nValue)
            {
                std::cout << primeNumbers[i] << " " << primeNumbers[j] << std::endl;
            }
        }
    }
}

int main()
{
    int n{};
    std::cout << "Enter N > 4: ";
    std::cin >> n;

    int endValue = (n + 1) / 2;

    bool primeNumbersInRange[endValue + 1];

    for (bool &value : primeNumbersInRange)
    {
        value = true;
    }

    findPrimeNumbersInRange(primeNumbersInRange, endValue);

    std::vector<int> primeNumbers;
    for (int i = 0; i <= endValue; i++)
    {
        if (primeNumbersInRange[i] == true)
        {
            primeNumbers.push_back(i);
        }
    }

    std::cout << "Pair of Prime Numbers p and q such that p * q < = " << n << " : " << std::endl;
    findPairOfPrimeNumbers(primeNumbers, n);

    return 0;
}