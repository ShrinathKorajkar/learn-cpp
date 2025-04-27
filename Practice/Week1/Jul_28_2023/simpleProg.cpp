#include <iostream>
#include <cstdint>
using namespace std;

/*
    1. Linker specify the starting point of program as main acc to Operating system's executable file format.
    2. main return's 0 exit status on successful exe and non-zero for other
    3. [[maybe_unused]] is used to supress warnings. can be used with functions too
    4. keywords :- 92
    5. endl flushes the buffer, \n do not
*/

int main()
{
    [[maybe_unused]] int a;
    int b = 2;   // copy initialization
    int c(3);    // direct initialization or constructor initialization
    int d{4};    // direct list initializaiton / Uniform initialization
    int e = {5}; // copy list initialization
    int f{};     // value initialization
    float g{4.3};
    int x = 42;
    decltype(x) y; // y is of type int

    cout << a << "\n"
         << b << "\n"
         << c << "\n"
         << d << "\n"
         << e << "\n"
         << f << "\n"
         << g << endl;

    // int num = 0;
    // cout << "\nEnter integer : ";
    // cin >> num;
    // cout << num << "\n";

    cout << "hello"
            "world\n";

    x = -1;
    unsigned int r = 2;
    unsigned int z = x;

    if (z > r)
    {
        cout << "x is greater: ";
        cout << z << endl;
    }
    else
    {
        cout << "r is greater: ";
    }

    std::cout << "Hello\fWorld" << std::endl;
    std::cout << "Line 1\rLine 2" << std::endl;

    a = (b = 3, b + 2);
    std::cout << a << std::endl;

    cout << "Unicode smiley: \u263A" << endl;
    std::cout << std::hex << 10 << std::endl;
    std::cout << std::dec << 10 << std::endl;

    std::cout << sizeof(int) << std::endl;
    std::cout << sizeof(long) << std::endl;
    std::cout << sizeof(long int) << std::endl;
    std::cout << sizeof(long long int) << std::endl;
    std::cout << sizeof(size_t) << std::endl
              << std::endl;

    // floating point
    double zero{0.0};
    double positiveInfinity{5.0 / zero};
    double negativeInfinity{-5.0 / zero};
    double nan{zero / zero};

    std::cout << positiveInfinity << std::endl;
    std::cout << negativeInfinity << std::endl;
    std::cout << nan << std::endl
              << std::endl;

    // bool
    bool bo{true};
    bool ao = 4;
    std::cout << std::boolalpha;
    std::cout << bo << std::endl;
    std::cout << std::noboolalpha;
    std::cout << ao << std::endl
              << std::endl;

    char input[100];
    cin.getline(input, sizeof(input)); // method to take leading spaces in char []

    std::int8_t myint{65};
    std::cout << myint << '\n'; // you're probably expecting this to print 65

    return 0;
}
