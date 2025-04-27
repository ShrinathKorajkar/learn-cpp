#ifndef TRAFFIC_SIGNAL_HPP
#define TRAFFIC_SIGNAL_HPP

#include <thread>
#include <vector>
#include <atomic>
#include <unordered_map>
#define DOTTEDLINE "-------------------------------------------------\n"

void printError(const char *message);
void printHeading(const std::string heading);

class TrafficLight
{
    int trafficLightId;
    int signalStatus;
    bool stopWorking = false;
    std::unordered_map<int, std::string> signals;

public:
    TrafficLight(const int &trafficLightId) : trafficLightId(trafficLightId), signalStatus(0)
    {
        signals.insert({0, " RED "});
        signals.insert({1, "GREEN"});
    }

    void signalController(const int &delayInSeconds, const int &noOfLanes);
    void stop();
    std::string getSignalStatus();
};

class TrafficJunction
{
    int noOfLanes;
    std::vector<TrafficLight> trafficLights;
    std::vector<std::thread> lanes;
    bool stopPrinting = false;

protected:
    virtual void checkForUserInterrupt();
    virtual void printStatus(const int &delayInSeconds);

public:
    TrafficJunction(const int &noOfLanes) : noOfLanes(noOfLanes)
    {
        for (auto i = 0; i < noOfLanes; i++)
        {
            trafficLights.emplace_back(TrafficLight(i));
        }
    }

    void startTrafficLights(const int &delayInSeconds);
    void stopTrafficLights();
};

void takeInput(int &noOfLanes, int &delayInSeconds);
#endif // !TRAFFIC_SIGNAL_HPP
