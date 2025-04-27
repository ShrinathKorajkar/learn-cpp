#include <iostream>
#include <random>

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dist(1, 10); // Generates integers in the range [1, 10]

    // Generate and print 5 random integers
    for (int i = 0; i < 5; ++i)
    {
        std::cout << dist(gen) << " ";
    }
    std::cout << std::endl;

    std::normal_distribution<double> dist2(0.0, 1.0); // Generates numbers following a normal distribution with mean 0 and standard deviation 1

    // Generate and print 5 random numbers following the normal distribution
    for (int i = 0; i < 5; ++i)
    {
        std::cout << dist2(gen) << " ";
    }
    std::cout << std::endl;

    std::bernoulli_distribution dist3(0.5); // Generates true or false with equal probability

    // Generate and print 5 random boolean values
    for (int i = 0; i < 5; ++i)
    {
        std::cout << std::boolalpha << dist3(gen) << " ";
    }
    std::cout << std::endl;

    std::vector<double> probabilities = {0.2, 0.1, 0.3, 0.4};

    // Create a discrete distribution using the probabilities
    std::discrete_distribution<int> dist4(probabilities.begin(), probabilities.end());

    // Generate and print 10 random outcomes
    for (int i = 0; i < 10; ++i)
    {
        std::cout << dist4(gen) << " ";
    }
    std::cout << std::endl;

    return 0;
}
