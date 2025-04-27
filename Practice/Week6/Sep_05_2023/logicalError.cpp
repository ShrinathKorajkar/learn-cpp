#include <iostream>
#include <stdexcept>
#include <cmath>

void createLogicalErrors(int x, int index)
{
    if (x < 0)
    {
        throw std::invalid_argument("Invalid Argument - No must be positive");
    }
    std::cout << "Sqrt : " << sqrt(x) << std::endl;

    if (x == 0)
    {
        throw std::domain_error("Input cannot be zero.");
    }
    std::cout << "Inverse : " << (float)1 / x << std::endl;

    int allowedLength = 10;
    if (x > allowedLength)
    {
        throw std::length_error("Lenght is greater than allowed");
    }
    int *arr = new int[x];

    if (index > x)
    {
        throw std::out_of_range("Index out of range");
    }
    std::cout << arr[index] << std::endl;

    delete arr;
}

int main()
{
    try
    {
        int index = 4, x = 5;
        createLogicalErrors(x, index);
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (const std::domain_error &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (const std::length_error &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        throw std::logic_error("logical error");
    }
    catch (...)
    {
        std::cout << "Error" << std::endl;
    }

    return 0;
}