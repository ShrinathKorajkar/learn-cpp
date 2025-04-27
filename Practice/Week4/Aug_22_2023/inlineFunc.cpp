#include <iostream>

class Greet
{
public:
    void greetMorning() { std::cout << "Good Morning" << std::endl; }
    __attribute__((noinline)) void greetAfternoon() { std::cout << "Good Afternoon" << std::endl; }
    void greetEvening();
    void greetNight() __attribute__((noinline));
    void greetDay();
    void greetHello() __attribute__((always_inline)) // only this got inline
    {
        std::cout << "Hello" << std::endl;
    }
};

inline void Greet::greetEvening() { std::cout << "Good Evening" << std::endl; }
void Greet::greetNight() { std::cout << "Good Night" << std::endl; }
void Greet::greetDay() { std::cout << "Good Day" << std::endl; }

int main()
{
    Greet g;
    g.greetMorning();
    g.greetAfternoon();
    g.greetEvening();
    g.greetNight();
    g.greetDay();
    g.greetHello();

    return 0;
}