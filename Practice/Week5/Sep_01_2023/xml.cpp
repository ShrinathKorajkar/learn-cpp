#include "pugixml.hpp"
#include <iostream>

int main()
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("./assets/file.xml");
    if (!result)
    {
        return -1;
    }
    else
    {
        pugi::xml_node employees = doc.first_child();
        for (pugi::xml_node employee : employees.children())
        {
            for (pugi::xml_node data : employee.children())
            {
                std::cout << data.child_value() << " ";
            }
            std::cout << std::endl;
        }
    }
}