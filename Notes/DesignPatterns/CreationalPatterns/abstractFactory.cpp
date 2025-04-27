#include <iostream>

/*
    Abstract Factory Pattern: ->  Provides an interface for creating families of related or dependent objects
    without specifying their concrete classes. It's often used in situations where a system must be independent
    of how its objects are created, composed, and represented.
*/

// Abstract products for a family of GUI components
class Button
{
public:
    virtual void render() = 0;
    virtual ~Button() {}
};

class TextBox
{
public:
    virtual void render() = 0;
    virtual ~TextBox() {}
};

// Concrete product classes for Windows GUI components
class WindowsButton : public Button
{
public:
    void render() override { std::cout << "Rendering Windows button" << std::endl; }
    ~WindowsButton() override { std::cout << "Destructor of WindowsButton" << std::endl; }
};

class WindowsTextBox : public TextBox
{
public:
    void render() override { std::cout << "Rendering Windows text box" << std::endl; }
    ~WindowsTextBox() override { std::cout << "Destructor of WindowsTextBox" << std::endl; }
};

// Concrete product classes for macOS GUI components
class MacOSButton : public Button
{
public:
    void render() override { std::cout << "Rendering macOS button" << std::endl; }
    ~MacOSButton() override { std::cout << "Destructor of MacOSButton" << std::endl; }
};

class MacOSTextBox : public TextBox
{
public:
    void render() override { std::cout << "Rendering macOS text box" << std::endl; }
    ~MacOSTextBox() override { std::cout << "Destructor of MacOSTextBox" << std::endl; }
};

// Abstract Factory interface for creating GUI components
class GUIFactory
{
public:
    virtual Button *createButton() = 0;
    virtual TextBox *createTextBox() = 0;
    virtual ~GUIFactory() {}
};

// Concrete Factory for creating Windows GUI components
class WindowsGUIFactory : public GUIFactory
{
public:
    Button *createButton() override { return new WindowsButton(); }
    TextBox *createTextBox() override { return new WindowsTextBox(); }
    ~WindowsGUIFactory() override { std::cout << "Destructor of WindowsGUIFactory" << std::endl; }
};

// Concrete Factory for creating macOS GUI components
class MacOSGUIFactory : public GUIFactory
{
public:
    Button *createButton() override { return new MacOSButton(); }
    TextBox *createTextBox() override { return new MacOSTextBox(); }
    ~MacOSGUIFactory() override { std::cout << "Destructor of MacOSGUIFactory" << std::endl; }
};

int main()
{
    GUIFactory *factory;

    factory = new WindowsGUIFactory();

    Button *button = factory->createButton();
    TextBox *textBox = factory->createTextBox();

    button->render();
    textBox->render();

    delete button;
    delete textBox;
    delete factory;

    return 0;
}
