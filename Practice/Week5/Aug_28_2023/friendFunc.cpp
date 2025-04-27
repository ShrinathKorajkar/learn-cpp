#include <iostream>

class Animal
{
    std::string name = "Tommy";
    int legs = 2;

    friend void changeName(Animal &obj, std::string name);

public:
    Animal() {}
    Animal(int legs) : legs(legs) {}
    void printName()
    {
        std::cout << name << std::endl;
    }

    friend Animal operator++(Animal &obj);
    friend Animal operator++(Animal &obj, int);
};

void changeName(Animal &obj, std::string name)
{
    obj.name = name;
}

Animal operator++(Animal &obj) // preincrement
{
    obj.legs = 4;
    return obj;
}

Animal operator++(Animal &obj, int) // postincrement
{
    Animal temp = obj;
    obj.legs++;
    return temp;
}

int main()
{
    Animal dog;
    changeName(dog, "Tiger");
    dog.printName();
    ++dog;
    return 0;
}