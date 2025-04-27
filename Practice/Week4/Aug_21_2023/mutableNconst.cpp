#include <iostream>

class MyClass
{
private:
    int value;
    mutable int mutableValue; // Can be modified even in const member functions

public:
    MyClass() : value(9), mutableValue(2) {}
    int getValue() const
    {
        mutableValue = 3;
        // value = 3; // error
        return value;
    }

    void setValue(int newValue)
    {
        value = newValue;
    }
};

int main()
{
    const MyClass constObj;
    MyClass nonConstObj;

    int val1 = constObj.getValue();
    int val2 = nonConstObj.getValue();

    // constObj.setValue(5);  // Error! Cannot modify a const object
    nonConstObj.setValue(10);

    std::cout << val2 << val1 << std::endl;

    return 0;
}
