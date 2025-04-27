#include <iostream>
#include <tuple>
#include <string>

int main()
{
    std::tuple<int, double, std::string> myTuple(42, 3.14159, "Hello");

    int intValue = std::get<0>(myTuple);
    double doubleValue = std::get<1>(myTuple);
    std::string stringValue = std::get<2>(myTuple);

    std::cout << "Integer: " << intValue << std::endl;
    std::cout << "Double: " << doubleValue << std::endl;
    std::cout << "String: " << stringValue << std::endl;

    std::tuple_element<1, decltype(myTuple)>::type element2Type;
    const int tupleSize = std::tuple_size<decltype(myTuple)>::value;

    std::cout << "Type of element at index 1: " << typeid(element2Type).name() << std::endl;
    std::cout << "Number of elements in the tuple: " << tupleSize << std::endl;

    auto [intVal, doubleVal, strVal] = myTuple;
    std::cout << "Structured Binding - Integer: " << intVal << ", Double: " << doubleVal << ", String: " << strVal << std::endl;

    return 0;
}
