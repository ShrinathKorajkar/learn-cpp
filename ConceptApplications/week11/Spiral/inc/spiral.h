#ifndef SPIRAL_H

#include <vector>

struct Coordinate
{
    int x;
    int y;

    Coordinate(int x, int y) : x(x), y(y) {}
};

enum Direction
{
    COUNTER_CLOCKWISE = -1,
    CLOCKWISE = 1
};

enum Side
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct SpiralParams
{
    Coordinate origin;
    int spiralStart;
    Direction spiralDirection;
    Side spiralStartSide;
};

void displaySpiral(int spiralSize, const SpiralParams &spiralParams);
std::vector<std::vector<int>> generateSpiral(int spiralSize, const SpiralParams &spiralParams);
Coordinate modifyCellCoordinates(const Coordinate &cell, const Side &startSide);
Coordinate adjustCellDirection(const Coordinate &cell, const Direction &direction);
int calculateCellValue(const Coordinate &modifiedCell, const SpiralParams &spiralParams);
Coordinate shiftCell(int rowIndex, int columnIndex, int spiralSize);
void printSpiral(const std::vector<std::vector<int>> &spiral);

#endif // !SPIRAL_H