#include <iostream>
#include <unordered_map>
#include <algorithm>

void populateCountryCodes(std::unordered_map<std::string, std::string> &countryCodes)
{
    countryCodes["IN"] = "India";
    countryCodes["US"] = "United States of America";
    countryCodes["UK"] = "United Kingdom";
    countryCodes["CA"] = "Canada";
    countryCodes["AU"] = "Australia";
    countryCodes["DE"] = "Germany";
    countryCodes["FR"] = "France";
    countryCodes["JP"] = "Japan";
    countryCodes["IT"] = "Italy";
    countryCodes["BR"] = "Brazil";
}

void convertIntoUpperCase(std::string &code)
{
    std::transform(code.begin(), code.end(), code.begin(), ::toupper);
}

bool validCountryCode(const std::unordered_map<std::string, std::string> &countryCodes, const std::string &code)
{
    return countryCodes.find(code) != countryCodes.end();
}

int main()
{
    std::unordered_map<std::string, std::string> countryCodes;

    populateCountryCodes(countryCodes);

    std::string code;
    std::cout << "Enter country code : ";
    std::cin >> code;

    convertIntoUpperCase(code);

    if (validCountryCode(countryCodes, code))
    {
        std::cout << "Country Name : " << countryCodes[code] << std::endl;
    }
    else
    {
        std::cout << "Invalid country code" << std::endl;
    }

    return 0;
}