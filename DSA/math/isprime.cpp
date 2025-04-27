#include <iostream>
#include <vector>

std::vector<int> seiveOfEratosthenes(int range)
{
    std::vector<int> primes(range + 1, 1);
    primes[0] = primes[1] = 0;
    for (int i = 2; i * i < range + 1; i++)
    {
        if (primes[i] == 1)
        {
            for (int j = i * i; j < range + 1; j += i)
            {
                primes[j] = 0;
            }
        }
    }
    return primes;
}

int main()
{
    int count = 0;
    std::vector<int> primes = seiveOfEratosthenes(100);
    for (int i = 0; i < primes.size(); i++)
    {
        if (primes[i])
        {
            count++;
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "count: " << count << std::endl;

    return 0;
}