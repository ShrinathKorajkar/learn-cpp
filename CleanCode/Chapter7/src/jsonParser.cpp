#include "jsonParser.h"

JsonValue JsonValue::operator[](const std::string &key)
{
    if (value[key].isNull())
    {
        throw JsonParseException("Value is not a string");
    }
    return JsonValue(value[key]);
}

JsonValue JsonValue::operator[](const int &key)
{
    if (!value.isValidIndex(key))
    {
        throw JsonParseException("Index is out of bounds");
    }
    if (value[key].isNull())
    {
        throw JsonParseException("Value is not a number");
    }
    return JsonValue(value[key]);
}

const JsonValue JsonValue::operator[](const std::string &key) const
{
    if (value[key].isNull())
    {
        throw JsonParseException("Value is not a string");
    }
    return JsonValue(value[key]);
}

const JsonValue JsonValue::operator[](const int &key) const
{
    if (!value.isValidIndex(key))
    {
        throw JsonParseException("Index is out of bounds");
    }
    if (value[key].isNull())
    {
        throw JsonParseException("Value is not a number");
    }
    return JsonValue(value[key]);
}

std::string JsonValue::as_string() const
{
    if (!value.isString())
    {
        throw JsonParseException("Value is not a string");
    }

    return value.asString();
}

double JsonValue::as_double() const
{
    if (!value.isNumeric())
    {
        throw JsonParseException("Value is not a number");
    }

    return value.asDouble();
}

bool JsonValue::as_bool() const
{
    if (!value.isBool())
    {
        throw JsonParseException("Value is not a boolean");
    }

    return value.asBool();
}

JsonValue JsonParser::parse(const std::string &json_data)
{
    bool status = json_reader.parse(json_data, json_root);
    if (!status || json_root.isNull())
    {
        throw JsonParseException(std::string("JSON parsing error: ") + json_reader.getFormattedErrorMessages());
    }
    return JsonValue(json_root);
}

JsonValue JsonParser::operator[](const std::string &key)
{
    try
    {
        return JsonValue(json_root[key]);
    }
    catch (const Json::LogicError &e)
    {
        throw JsonParseException(std::string("JSON logic error: ") + e.what());
    }
}

JsonValue JsonParser::operator[](const int &key)
{
    try
    {
        return JsonValue(json_root[static_cast<Json::ArrayIndex>(key)]);
    }
    catch (const Json::LogicError &e)
    {
        throw JsonParseException(std::string("JSON logic error: ") + e.what());
    }
}
