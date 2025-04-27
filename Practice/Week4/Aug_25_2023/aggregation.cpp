#include <iostream>
#include <string>
#include <vector>

class Engine
{
private:
    std::string type;

public:
    Engine(const std::string &_type) : type(_type) {}

    void start()
    {
        std::cout << "Starting the " << type << " engine.\n";
    }
};

class Car
{
private:
    std::string model;
    Engine *engine; // Aggregation: Car has an Engine, but Engine can exist independently
public:
    Car(const std::string &_model, Engine *_engine) : model(_model), engine(_engine) {}

    void start()
    {
        std::cout << "Starting the " << model << " car.\n";
        engine->start(); // Delegates starting the engine to the Engine object
    }
};

int main()
{
    Engine *carEngine = new Engine("V6");
    Car *myCar = new Car("Toyota Camry", carEngine);

    myCar->start(); // Starts both the car and the engine

    delete myCar; // Clean up dynamic memory
    delete carEngine;

    return 0;
}
