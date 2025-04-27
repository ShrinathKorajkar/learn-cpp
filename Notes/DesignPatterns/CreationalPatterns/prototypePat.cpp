#include <iostream>
#include <string>

/*
    Prototype Pattern  ->  Creates new objects by copying an existing object, known as the prototype.
    This pattern is useful when the cost of creating an object is more expensive than copying it.
*/

// Abstract base class for prototype objects
class Prototype
{
public:
    virtual Prototype *clone() const = 0;
    virtual void displayInfo() const = 0;
    virtual ~Prototype() {}
};

// Concrete prototype class
class ConcretePrototype : public Prototype
{
    int id_;
    std::string name_;

public:
    ConcretePrototype(int id, const std::string &name) : id_(id), name_(name) {}
    // Copy constructor for cloning
    ConcretePrototype(const ConcretePrototype &other) : id_(other.id_), name_(other.name_) {}
    Prototype *clone() const override { return new ConcretePrototype(*this); }
    void displayInfo() const override { std::cout << "ID: " << id_ << ", Name: " << name_ << std::endl; }
};

int main()
{
    Prototype *prototype = new ConcretePrototype(1, "Prototype 1");

    Prototype *clone1 = prototype->clone();
    Prototype *clone2 = prototype->clone();

    std::cout << "Original Prototype:" << std::endl;
    prototype->displayInfo();

    std::cout << "Clone 1:" << std::endl;
    clone1->displayInfo();

    std::cout << "Clone 2:" << std::endl;
    clone2->displayInfo();

    delete prototype;
    delete clone1;
    delete clone2;

    return 0;
}
