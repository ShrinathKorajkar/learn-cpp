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
    Engine engine; // Composition: Car "has-a" Engine, and Engine is part of Car
public:
    Car(const std::string &_model, const std::string &engineType) : model(_model), engine(engineType) {}

    void start()
    {
        std::cout << "Starting the " << model << " car.\n";
        engine.start(); // Starts the engine, which is part of the car
    }
};

int main()
{
    Car myCar("Toyota Camry", "V6");

    myCar.start(); // Starts both the car and the engine

    return 0;
}
