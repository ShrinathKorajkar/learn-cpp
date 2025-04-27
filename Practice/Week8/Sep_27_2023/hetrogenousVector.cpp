#include <iostream>
#include <vector>
#include <variant>
#include <any>

int main()
{
    std::vector<std::variant<int, double, std::string>> heterogeneousVector;
    heterogeneousVector.push_back(42);
    heterogeneousVector.push_back(3.14);
    heterogeneousVector.push_back("Hello, World!");

    for (const auto &element : heterogeneousVector)
    {
        if (std::holds_alternative<int>(element))
        {
            std::cout << "It's an integer: " << std::get<int>(element) << std::endl;
        }
        else if (std::holds_alternative<double>(element))
        {
            std::cout << "It's a double: " << std::get<double>(element) << std::endl;
        }
        else if (std::holds_alternative<std::string>(element))
        {
            std::cout << "It's a string: " << std::get<std::string>(element) << std::endl;
        }
    }

    std::vector<std::any> heterogeneousVector2;
    heterogeneousVector2.push_back(42);
    heterogeneousVector2.push_back(3.14);
    heterogeneousVector2.push_back(std::string("Hello, World!"));

    for (const auto &element : heterogeneousVector2)
    {
        if (element.type() == typeid(int))
        {
            std::cout << "It's an integer: " << std::any_cast<int>(element) << std::endl;
        }
        else if (element.type() == typeid(double))
        {
            std::cout << "It's a double: " << std::any_cast<double>(element) << std::endl;
        }
        else if (element.type() == typeid(std::string))
        {
            std::cout << "It's a string: " << std::any_cast<std::string>(element) << std::endl;
        }
    }

    return 0;
}
