#include <iostream>

class Animal
{
public:
    void makeSound()
    {
        std::cout << "Animal sound" << std::endl;
    }
};

class Dog : public Animal
{
public:
    void makeSound()
    {
        std::cout << "Dog barks" << std::endl;
    }
};

class Cat : public Animal
{
public:
    void makeSound()
    {
        std::cout << "Cat meows" << std::endl;
    }
};

class Cow : public Animal
{
public:
    void makeSound()
    {
        std::cout << "Cow moos" << std::endl;
    }
};

int main()
{
    Dog dog;
    Cat cat;
    Cow cow;

    dog.makeSound();
    cat.makeSound();
    cow.makeSound();

    return 0;
}
