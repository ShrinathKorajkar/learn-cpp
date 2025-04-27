#include <iostream>

// State interface
class TrafficLightState
{
public:
    virtual void handle() = 0;
};

// Concrete States
class RedLightState : public TrafficLightState
{
public:
    void handle() override
    {
        std::cout << "Red Light - Stop!" << std::endl;
    }
};

class GreenLightState : public TrafficLightState
{
public:
    void handle() override
    {
        std::cout << "Green Light - Go!" << std::endl;
    }
};

class YellowLightState : public TrafficLightState
{
public:
    void handle() override
    {
        std::cout << "Yellow Light - Prepare to Stop!" << std::endl;
    }
};

// Context
class TrafficLight
{
public:
    TrafficLight() : state_(nullptr) {}

    void setState(TrafficLightState *state)
    {
        state_ = state;
    }

    void change()
    {
        if (state_ == nullptr)
        {
            std::cout << "Initializing the traffic light..." << std::endl;
            state_ = new RedLightState();
        }
        else if (color == "redLight")
        {
            state_ = new GreenLightState();
            color = "greenLight";
        }
        else if (color == "greenLight")
        {
            state_ = new YellowLightState();
            color = "yellowLight";
        }
        else if (color == "yellowLight")
        {
            state_ = new RedLightState();
            color = "redLight";
        }

        state_->handle();
    }

private:
    TrafficLightState *state_;
    std::string color = "redLight";
};

int main()
{
    TrafficLight trafficLight;

    trafficLight.change();
    trafficLight.change();
    trafficLight.change();
    trafficLight.change();

    return 0;
}
