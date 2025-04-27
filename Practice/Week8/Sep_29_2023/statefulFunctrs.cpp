#include <iostream>

struct Counter
{
    int count;
    Counter() : count(0) {}
    void operator()()
    {
        count++;
        std::cout << "Called " << count << " times." << std::endl;
    }
};

int main()
{
    Counter counter;
    counter();
    counter();
    counter();

    return 0;
}
