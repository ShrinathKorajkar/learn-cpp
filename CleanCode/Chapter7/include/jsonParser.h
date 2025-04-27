#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <json/json.h>
#include <stdexcept>

/**
 * @brief Custom exception class for JSON parsing errors.
 */
class JsonParseException : public std::runtime_error
{
public:
    explicit JsonParseException(const std::string &message)
        : std::runtime_error(message) {}
};

/**
 * @brief Wrapper class for Json::Value providing additional functionality.
 */
class JsonValue
{

private:
    Json::Value &value;

public:
    JsonValue(Json::Value &value) : value(value) {}

    JsonValue operator[](const std::string &key);
    JsonValue operator[](const int &key);

    const JsonValue operator[](const std::string &key) const;
    const JsonValue operator[](const int &key) const;

    std::string as_string() const;
    double as_double() const;
    bool as_bool() const;
};

/**
 * @brief Class for parsing JSON data.
 */
class JsonParser
{

private:
    Json::Value json_root;
    Json::Reader json_reader;

public:
    JsonParser() = default;
    ~JsonParser() = default;
    JsonValue parse(const std::string &json_data);
    JsonValue operator[](const std::string &key);
    JsonValue operator[](const int &key);
};

#endif
