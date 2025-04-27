#include <iostream>

int execute()
{
    std::cout << "Inside execute()" << std::endl;
    exit(EXIT_SUCCESS);
}

static int s = execute();

int main()
{
    std::cout << "Inside main() - never executed";
}