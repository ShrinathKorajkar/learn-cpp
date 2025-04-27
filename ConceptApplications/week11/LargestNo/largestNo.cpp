#include <iostream>

#include "largestNo.h"

int getLargestNumber(const int array[], int size)
{
    if (size == 0)
    {
        throw std::runtime_error("Invalid Array");
    }

    int largest = array[0];
    for (int i = 1; i < size; i++)
    {
        if (array[i] > largest)
        {
            largest = array[i];
        }
    }
    return largest;
}
