#include <iostream>
#include <limits>
#include "trafficSignal.hpp"

void startTrafficLightSystem(const int &noOfLanes, const int &delayInSeconds)
{
    TrafficJunction junction(noOfLanes);
    junction.startTrafficLights(delayInSeconds);
}

int main()
{
    int noOfLanes = 0;
    int delayInSeconds = 10;

    printHeading("TRAFFIC LIGHT SYSTEM");

    takeInput(noOfLanes, delayInSeconds);

    startTrafficLightSystem(noOfLanes, delayInSeconds);

    return 0;
}