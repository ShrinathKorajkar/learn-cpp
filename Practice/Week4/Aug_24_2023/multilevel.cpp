#include <iostream>

class Vehicle
{
public:
    void display()
    {
        std::cout << "Vehicle" << std::endl;
    }
};

class Car : public Vehicle
{
public:
    void display()
    {
        std::cout << "Car" << std::endl;
    }
};

class SportsCar : public Car
{
public:
    void display()
    {
        std::cout << "Sports Car" << std::endl;
    }
};

int main()
{
    SportsCar sportsCar;
    sportsCar.display();

    Car car;
    car.display();

    Vehicle vehicle;
    vehicle.display();
    return 0;
}
