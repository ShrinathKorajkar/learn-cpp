#include "spiral.h"
#include <cmath>
#include <iomanip>
#include <iostream>

void displaySpiral(int spiralSize, const SpiralParams &spiralParams)
{
    if (spiralSize % 2 == 0)
    {
        throw std::invalid_argument("Please provide an odd number for n to generate a symmetric spiral.");
    }

    std::vector<std::vector<int>> spiral = generateSpiral(spiralSize, spiralParams);
    printSpiral(spiral);
}

std::vector<std::vector<int>> generateSpiral(int spiralSize, const SpiralParams &spiralParams)
{
    std::vector<std::vector<int>> spiral(spiralSize, std::vector<int>(spiralSize, 0));

    for (int rowIndex = -spiralSize / 2; rowIndex <= spiralSize / 2; ++rowIndex)
    {
        for (int columnIndex = -spiralSize / 2; columnIndex <= spiralSize / 2; ++columnIndex)
        {
            Coordinate spiralCell(rowIndex, columnIndex);

            Coordinate modifiedCell = modifyCellCoordinates(spiralCell, spiralParams.spiralStartSide);
            modifiedCell = adjustCellDirection(modifiedCell, spiralParams.spiralDirection);
            int value = calculateCellValue(modifiedCell, spiralParams);

            // shift cells to make spiral start from (0,0) index for storing spiral
            Coordinate shiftedCell = shiftCell(rowIndex, columnIndex, spiralSize);

            spiral[shiftedCell.x][shiftedCell.y] = value;
        }
    }

    return spiral;
}

Coordinate shiftCell(int rowIndex, int columnIndex, int spiralSize)
{
    int xCoordinate = rowIndex + spiralSize / 2;
    int yCoordinate = columnIndex + spiralSize / 2;

    return Coordinate(xCoordinate, yCoordinate);
}

Coordinate modifyCellCoordinates(const Coordinate &cell, const Side &startSide)
{
    Coordinate newCell = cell;

    switch (startSide)
    {
    case LEFT:
    {
        int temp = newCell.x;
        newCell.x = newCell.y;
        newCell.y = -temp;
        break;
    }
    case DOWN:
    {
        newCell.x = -newCell.x;
        newCell.y = -newCell.y;
        break;
    }
    case RIGHT:
    {
        int temp = newCell.x;
        newCell.x = -newCell.y;
        newCell.y = temp;
        break;
    }
    default:
        break;
    }

    return newCell;
}

Coordinate adjustCellDirection(const Coordinate &cell, const Direction &direction)
{
    Coordinate newCell = cell;
    newCell.y *= direction;
    return newCell;
}

int calculateCellValue(const Coordinate &modifiedCell, const SpiralParams &spiralParams)
{
    int distFromOriginX = modifiedCell.x - spiralParams.origin.x;
    int distFromOriginY = modifiedCell.y - spiralParams.origin.y;

    int layerOfCell = std::max(std::abs(distFromOriginX), std::abs(distFromOriginY));

    int middleCellPosition = 4 * layerOfCell * layerOfCell;

    int directionFromMiddleCell = (distFromOriginY > distFromOriginX) ? COUNTER_CLOCKWISE : CLOCKWISE;

    int distFromMiddleCell = 2 * layerOfCell - (distFromOriginX + distFromOriginY);

    int cellValue = spiralParams.spiralStart + middleCellPosition + directionFromMiddleCell * distFromMiddleCell;

    return cellValue;
}

void printSpiral(const std::vector<std::vector<int>> &spiral)
{
    int spiralSize = spiral.size();
    int maxDigits = std::to_string(spiralSize * spiralSize).length();

    for (const auto &row : spiral)
    {
        for (const auto &cell : row)
        {
            std::cout << std::setw(maxDigits) << cell << " ";
        }
        std::cout << std::endl;
    }
}
