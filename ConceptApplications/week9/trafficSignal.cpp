#include <iostream>
#include <iomanip>
#include <SFML/Window/Event.hpp>
#include "trafficSignal.hpp"

void printError(const char *message)
{
    if (message != nullptr)
    {
        std::cout << message << std::endl;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();
}

void printHeading(const std::string heading)
{
    std::cout << std::endl;
    std::cout << DOTTEDLINE;
    int desiredLength = 44;
    int headingLength = heading.length();
    if (headingLength < 45)
    {
        int fillLength1 = (desiredLength - headingLength) / 2 - 1;
        int fillLength2 = (desiredLength - headingLength) / 2;
        if (headingLength % 2 != 0)
        {
            fillLength1++;
        }
        std::string fill1(fillLength1, ' ');
        std::string fill2(fillLength2, ' ');
        std::cout << "---" << fill1 << heading << fill2 << "---" << std::endl;
    }
    else
    {
        std::cout << heading << std::endl;
    }
    std::cout << DOTTEDLINE;
}

void TrafficLight::signalController(const int &delayInSeconds, const int &noOfLanes)
{
    std::this_thread::sleep_for(std::chrono::seconds(trafficLightId * delayInSeconds));
    long currentDelay = 0;
    long maxDelay = delayInSeconds * (noOfLanes - 1);
    signalStatus = signalStatus == 0 ? 1 : 0;
    while (!stopWorking)
    {
        currentDelay++;
        if (signalStatus == 0 && currentDelay >= maxDelay)
        {
            currentDelay = 0;
            signalStatus = signalStatus == 0 ? 1 : 0;
        }
        else if (signalStatus == 1 && currentDelay >= delayInSeconds)
        {
            currentDelay = 0;
            signalStatus = signalStatus == 0 ? 1 : 0;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void TrafficLight::stop()
{
    stopWorking = true;
}

std::string TrafficLight::getSignalStatus()
{
    return signals[signalStatus];
}

void TrafficJunction::checkForUserInterrupt()
{
    while (true)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            stopPrinting = true;
            break;
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    stopTrafficLights();
}

void TrafficJunction::printStatus(const int &delayInSeconds)
{
    std::cout << "\nPress Q to quit\n\n";
    std::cout << "LANE NO    INDICATOR" << std::endl;
    std::cout << "\033\[s";
    while (!stopPrinting)
    {
        std::cout << "\033\[u";
        for (int i = 0; i < noOfLanes; i++)
        {
            std::cout << std::setw(3) << "" << std::left << std::setw(10) << i + 1 << std::setw(5) << trafficLights[i].getSignalStatus() << std::endl;
        }
        std::cout << std::endl;
        int delay = delayInSeconds;
        while (delay > 0 && !stopPrinting)
        {
            std::cout << "\rRemaining Time : " << std::setw(10) << delay;
            std::cout.flush();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            delay--;
        }
    }
}

void TrafficJunction::startTrafficLights(const int &delayInSeconds)
{
    for (auto i = 0; i < noOfLanes; i++)
    {
        lanes.emplace_back(&TrafficLight::signalController, &trafficLights[i], delayInSeconds, noOfLanes);
    }
    std::thread thread([this]()
                       { this->checkForUserInterrupt(); });
    printStatus(delayInSeconds);
    thread.join();
}

void TrafficJunction::stopTrafficLights()
{
    stopPrinting = true;
    std::cout << "\n\nTurning Signals OFF ..." << std::endl;
    for (auto &lights : trafficLights)
    {
        lights.stop();
    }
    for (auto &lane : lanes)
    {
        if (lane.joinable())
        {
            lane.join();
        }
    }
    std::cout << "\nTraffic Signals Stopped" << std::endl;
}

void takeInput(int &noOfLanes, int &delayInSeconds)
{
    while (true)
    {
        std::cout << "Enter the number of Lanes : ";
        std::cin >> noOfLanes;
        if (std::cin.fail())
        {
            printError("Invalid Input !... Please enter a number");
            std::cout << std::endl;
        }
        else if (noOfLanes < 3)
        {
            std::cout << "No of lanes must be greate than 2.\n\n";
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        std::cout << "Enter Delay in Traffic Signals in seconds : ";
        std::cin >> delayInSeconds;
        if (std::cin.fail() || delayInSeconds < 1)
        {
            printError("Invalid Input !... Please enter a positive integer");
            std::cout << std::endl;
        }
        else
        {
            break;
        }
    }
}
