#include <iostream>

// Doxygen
/**
 * @brief This is a brief description of the function.
 *
 * This is a more detailed description of the function. You can use
 * multiple lines for more details.
 *
 * @param param1 Description of the first parameter.
 * @param param2 Description of the second parameter.
 * @return Description of the return value.
 */
int myFunction1(int param1, int param2)
{
    std::cout << "Function with Doxygen Style comments" << std::endl;
}

//
// QT style
/*!
 * \brief Brief description of the function.
 *
 * Detailed description of the function.
 *
 * \param param1 Description of the first parameter.
 * \param param2 Description of the second parameter.
 * \return Description of the return value.
 */
int myFunction2(int param1, int param2)
{
    std::cout << "Function with QT Style comments" << std::endl;
}

//
//
// Simple Comments
// This function does something.
// Parameters:
//   param1: Description of the first parameter.
//   param2: Description of the second parameter.
// Returns: Description of the return value.
int myFunction3(int param1, int param2)
{
    std::cout << "Function with Simple comments" << std::endl;
}

int main()
{
    myFunction1(1, 2);

    myFunction2(2, 3);

    myFunction3(4, 3);
    return 0;
}
