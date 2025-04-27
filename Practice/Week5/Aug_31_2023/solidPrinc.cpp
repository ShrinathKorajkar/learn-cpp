#include <iostream>
#include <cstring>

// Single Responsibility Principle (SRP)
class FileManager
{
public:
    void readFromFile() {}
    void writeToFile() {}
};

// Open/Closed Principle (OCP)
class Shape
{
public:
    virtual double area() const = 0;
};
class Circle : public Shape
{
public:
    double area() const override {}
};

// Liskov Substitution Principle (LSP) -> use dynamic polymorphism
class Bird
{
public:
    virtual void fly() {}
};

class Sparrow : public Bird
{
public:
    void fly() override {}
};

// Interface Segregation Principle (ISP)
class Worker
{
public:
    virtual void work() = 0;
};
class Engineer : public Worker
{
public:
    void work() override {}
};

class Artist : public Worker
{
public:
    void work() override {}
};

// Dependency Inversion Principle (DIP)
class Logger
{
public:
    virtual void log(const std::string &message) = 0;
};

class ConsoleLogger : public Logger
{
public:
    void log(const std::string &message) override {}
};

class Application
{
private:
    Logger *logger;

public:
    Application(Logger *logger) : logger(logger) {}
    void doSomething() {}
};
