#include <iostream>

class Calculator
{

private:
    int result;

public:
    Calculator() : result(0) {}

    Calculator &add(int value)
    {
        result += value;
        return *this; // Return a reference to the current object
    }

    Calculator &subtract(int value)
    {
        result -= value;
        return *this; // Return a reference to the current object
    }

    Calculator &multiply(int value)
    {
        result *= value;
        return *this; // Return a reference to the current object
    }

    Calculator &divide(int value)
    {
        if (value != 0)
        {
            result /= value;
        }
        else
        {
            std::cout << "Error: Division by zero\n";
        }
        return *this; // Return a reference to the current object
    }

    int getResult() const
    {
        return result;
    }
};

int main()
{
    Calculator calc;

    int finalResult = calc.add(10).multiply(2).subtract(5).divide(2).getResult();

    std::cout << "Final result: " << finalResult << std::endl; // Output: Final result: 5

    return 0;
}
