/*
    Observer Pattern:  ->  Defines a one-to-many dependency between objects, so that when one object
    changes state, all its dependents are notified and updated automatically.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Observer interface
class Observer
{
public:
    virtual void update(const std::string &message) = 0;
    virtual ~Observer() {}
};

// Concrete Observer class
class ConcreteObserver : public Observer
{
public:
    ConcreteObserver(const std::string &name) : name_(name) {}

    void update(const std::string &message) override
    {
        std::cout << name_ << " received message: " << message << std::endl;
    }

private:
    std::string name_;
};

// Subject interface
class Subject
{
public:
    virtual void attach(Observer *observer) = 0;
    virtual void detach(Observer *observer) = 0;
    virtual void notify(const std::string &message) = 0;
    virtual ~Subject() {}
};

// Concrete Subject class
class ConcreteSubject : public Subject
{
public:
    void attach(Observer *observer) override
    {
        observers_.push_back(observer);
    }

    void detach(Observer *observer) override
    {
        // Find and remove the observer from the list
        auto it = std::find(observers_.begin(), observers_.end(), observer);
        if (it != observers_.end())
        {
            observers_.erase(it);
        }
    }

    void notify(const std::string &message) override
    {
        for (Observer *observer : observers_)
        {
            observer->update(message);
        }
    }

private:
    std::vector<Observer *> observers_;
};

int main()
{
    // Create a subject
    ConcreteSubject subject;

    // Create observers
    ConcreteObserver observer1("Observer 1");
    ConcreteObserver observer2("Observer 2");

    // Attach observers to the subject
    subject.attach(&observer1);
    subject.attach(&observer2);

    // Notify observers of a state change
    subject.notify("Hello, observers!");

    // Detach an observer
    subject.detach(&observer1);

    // Notify remaining observer
    subject.notify("Observer 1 detached.");

    return 0;
}
