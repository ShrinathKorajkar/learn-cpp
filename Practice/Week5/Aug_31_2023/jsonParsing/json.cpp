#include "json/json.h"
#include <iostream>
#include <fstream>
#include <memory>

int main()
{
    // const std::string rawJson = R"({"Age": 20, "Name": "colin"})";
    std::ifstream file("./assets/file.json");

    Json::Value root;
    Json::Reader reader;
    reader.parse(file, root);

    for (const auto &entry : root)
    {
        const int empId = entry["EMPID"].asInt();
        std::cout << "EmpId: " << empId << std::endl;
    }

    // const std::string name = root["Name"].asString();
    // const int age = root["Age"].asInt();

    // std::cout << root;
    // std::cout << name << std::endl;
    // std::cout << age << std::endl;
    return EXIT_SUCCESS;
}