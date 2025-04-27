#include <iostream>

class Engine
{
public:
    void start()
    {
        std::cout << "Engine started" << std::endl;
    }
};

class Wheel
{
public:
    void run()
    {
        std::cout << "Moving" << std::endl;
    }
};

class Car
{
    Engine engine;   // Composition
    Wheel wheels[4]; // aggregation
public:
    void startCar()
    {
        engine.start();
        std::cout << "Car started" << std::endl;
    }
    void moveCar()
    {
        for (int i = 0; i < 4; i++)
        {
            wheels[i].run();
        }
    }
};

class Person
{
    Car *car; // association
};

int main()
{
    Car car;
    car.startCar();

    return 0;
}
