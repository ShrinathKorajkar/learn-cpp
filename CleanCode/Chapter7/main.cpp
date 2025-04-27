#include "locationFinder.h"
#include <iostream>

int main()
{
    LocationFinder location_finder;
    std::string user_input;

    while (true)
    {
        std::cout << "\nEnter Address to search for: ";
        std::getline(std::cin, user_input);

        try
        {
            Location location = location_finder.find_location(user_input);
            std::cout << "\nFound Address : " << location.name << std::endl;
            std::cout << "Latitude : " << location.latitude
                      << "\nLongitude : " << location.longitude
                      << std::endl;
            break;
        }
        catch (std::exception &e)
        {
            std::cout << "Address not found! Try Again" << std::endl;
        }
    }

    std::cout << std::endl;

    return 0;
}