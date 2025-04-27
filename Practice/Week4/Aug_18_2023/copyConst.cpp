#include <iostream>
#include <cstring>

class Vehicle
{
    const int wheels;
    int &id;
    char *color;
    static const int myStaticConstant = 100;

public:
    Vehicle(int &id) : wheels(2), id(id)
    {
        color = new char[10]{"black"};
    }

    Vehicle(const Vehicle &other) : wheels(other.wheels), id(other.id)
    {
        color = new char[strlen(other.color) + 1];
        strcpy(color, other.color);
    }

    ~Vehicle()
    {
        delete[] color;
    }

    void printVehicle()
    {
        std::cout << "Id " << id << " : " << color << " : " << wheels << std::endl;
        std::cout << "Static Constant : " << myStaticConstant << std::endl;
    }
};

int main()
{
    int id = 2;
    Vehicle honda(id);
    Vehicle hero(honda);

    honda.printVehicle();
    hero.printVehicle();
    return 0;
}