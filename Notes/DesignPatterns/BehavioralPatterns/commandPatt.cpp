/*
    Command Pattern:  ->  Encapsulates a request as an object, thereby allowing for parameterization
    of clients with queues, requests, and operations.
*/
#include <iostream>

// Forward declaration of LightReceiver class
class LightReceiver;

// Command interface
class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() {}
};

// ConcreteCommand 1: Light On Command
class LightOnCommand : public Command
{
public:
    LightOnCommand(LightReceiver *light);
    void execute() override;

private:
    LightReceiver *light_;
};

// ConcreteCommand 2: Light Off Command
class LightOffCommand : public Command
{
public:
    LightOffCommand(LightReceiver *light);
    void execute() override;

private:
    LightReceiver *light_;
};

// Receiver
class LightReceiver
{
public:
    void turnOn()
    {
        std::cout << "Light is on" << std::endl;
    }

    void turnOff()
    {
        std::cout << "Light is off" << std::endl;
    }
};

// Implementations of ConcreteCommand constructors
LightOnCommand::LightOnCommand(LightReceiver *light) : light_(light) {}
LightOffCommand::LightOffCommand(LightReceiver *light) : light_(light) {}

// Implementations of ConcreteCommand execute methods
void LightOnCommand::execute()
{
    light_->turnOn();
}

void LightOffCommand::execute()
{
    light_->turnOff();
}

// Invoker
class RemoteControl
{
public:
    void setCommand(Command *command)
    {
        command_ = command;
    }

    void pressButton()
    {
        command_->execute();
    }

private:
    Command *command_;
};

int main()
{
    // Create a receiver
    LightReceiver light;

    // Create concrete command objects
    LightOnCommand onCommand(&light);
    LightOffCommand offCommand(&light);

    // Create an invoker and set the command
    RemoteControl remote;
    remote.setCommand(&onCommand);

    // Press the button to turn on the light
    remote.pressButton();

    // Change the command and press the button again to turn off the light
    remote.setCommand(&offCommand);
    remote.pressButton();

    return 0;
}
