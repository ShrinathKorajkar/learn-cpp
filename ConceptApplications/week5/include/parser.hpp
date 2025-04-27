#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include "csv.h"
#include "json/json.h"
#include "pugixml.hpp"
#define CSV_FILE_PATH "./assets/file.csv"
#define JSON_FILE_PATH "./assets/file.json"
#define XML_FILE_PATH "./assets/file.xml"

class Employee
{
    int empId{};
    std::string name;
    int age{};
    int joiningYear{};

public:
    Employee() = default;
    void setData(const int &id, const std::string &name, const int &age, const int &joiningYear);
    friend std::ostream &operator<<(std::ostream &outputStream, const Employee &employee);
};

class Parser
{
protected:
    int employeeId{};
    std::string name;
    int age{};
    int yearOfJoining{};

public:
    virtual void parseFile() = 0;
    virtual ~Parser() = default;
};

class CsvParser : public Parser
{
    io::CSVReader<4> in;

public:
    CsvParser() : in(CSV_FILE_PATH) {}
    void parseFile() override;
    virtual ~CsvParser() = default;
};

class JsonParser : public Parser
{
    std::ifstream file;
    Json::Value root;
    Json::Reader reader;

public:
    JsonParser() : file(JSON_FILE_PATH) {}
    void parseFile() override;
    virtual ~JsonParser() = default;
};

class XmlParser : public Parser
{
    pugi::xml_document doc;
    pugi::xml_parse_result result;

public:
    XmlParser() : result(doc.load_file(XML_FILE_PATH)) {}
    void parseFile() override;
    virtual ~XmlParser() = default;
};

#endif // !PARSER_H
