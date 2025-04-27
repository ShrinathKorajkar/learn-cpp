/*
    Composite Pattern  ->  Composes objects into tree structures to represent part-whole hierarchies.
    It allows clients to treat individual objects and compositions of objects uniformly.
*/

#include <iostream>
#include <vector>
#include <algorithm>

// Component interface that declares the common operations for both leaf and composite objects
class Component
{
public:
    virtual void operation() = 0;
    virtual ~Component() {}
};

// Leaf class representing individual objects
class Leaf : public Component
{
public:
    Leaf(const std::string &name) : name_(name) {}

    void operation() override
    {
        std::cout << "Leaf: " << name_ << std::endl;
    }

private:
    std::string name_;
};

// Composite class representing a group of objects (compositions)
class Composite : public Component
{
public:
    void operation() override
    {
        std::cout << "Composite:" << std::endl;
        for (Component *component : components_)
        {
            component->operation();
        }
    }

    void add(Component *component)
    {
        components_.push_back(component);
    }

    void remove(Component *component)
    {
        // Find the iterator pointing to the component
        auto it = std::find(components_.begin(), components_.end(), component);

        if (it != components_.end())
        {
            components_.erase(it); // Erase the component using the iterator
        }
    }

private:
    std::vector<Component *> components_;
};

int main()
{
    // Create leaf objects
    Component *leaf1 = new Leaf("Leaf 1");
    Component *leaf2 = new Leaf("Leaf 2");
    Component *leaf3 = new Leaf("Leaf 3");

    // Create a composite object and add leaf objects to it
    Composite *composite = new Composite();
    composite->add(leaf1);
    composite->add(leaf2);

    // Create another composite object and add a leaf and the first composite to it
    Composite *composite2 = new Composite();
    composite2->add(leaf3);
    composite2->add(composite);

    // Call the operation method on the second composite to display the whole hierarchy
    composite2->operation();

    // Clean up resources
    delete leaf1;
    delete leaf2;
    delete leaf3;
    delete composite;
    delete composite2;

    return 0;
}
