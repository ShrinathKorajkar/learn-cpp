#include <iostream>
#include <type_traits>

template <typename T>
void processType(const T &value)
{
    if constexpr (std::is_integral<T>::value)
    {
        std::cout << "Processing an integral type: " << value << std::endl;
    }
    else if constexpr (std::is_floating_point<T>::value)
    {
        std::cout << "Processing a floating-point type: " << value << std::endl;
    }
    else
    {
        std::cout << "Processing other types: " << value << std::endl;
    }
}

// type dispatch
template <typename T>
void process(T value, std::true_type)
{
    std::cout << "Integral: " << value << std::endl;
}

template <typename T>
void process(T value, std::false_type)
{
    std::cout << "Floating-point: " << value << std::endl;
}

template <typename T>
void process(T value)
{
    process(value, std::is_integral<T>());
}

// SFINAE
template <typename T, typename = void>
struct SpecializationSelector
{
    static void display()
    {
        std::cout << "Generic Template" << std::endl;
    }
};

template <typename T>

struct SpecializationSelector<T, std::enable_if_t<std::is_integral_v<T>>>
{
    static void display()
    {
        std::cout << "Specialization for Integral Types" << std::endl;
    }
};

template <typename T>
struct SpecializationSelector<T, std::enable_if_t<!std::is_integral_v<T>>>
{
    static void display()
    {
        std::cout << "Specialization for Non-Integral Types" << std::endl;
    }
};

int main()
{
    processType(42);
    processType(3.14);
    processType("Hello");

    process(40);

    SpecializationSelector<int>::display();
    SpecializationSelector<double>::display();
    SpecializationSelector<std::string>::display();
    return 0;
}
