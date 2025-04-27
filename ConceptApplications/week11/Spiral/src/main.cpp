#include "spiral.h"
#include <iostream>

int main()
{
    int spiralSize = 5;
    Coordinate origin(0, 0);
    int spiralStart = 0;
    Direction spiralDirection = COUNTER_CLOCKWISE;
    Side spiralStartSide = RIGHT;

    SpiralParams spiralParams{origin, spiralStart, spiralDirection, spiralStartSide};

    try
    {
        displaySpiral(spiralSize, spiralParams);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
