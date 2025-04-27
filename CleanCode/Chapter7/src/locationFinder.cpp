#include "locationFinder.h"

LocationFinder::LocationFinder() : web_connector(WebConnector::get_instance())
{
    char *env_value = std::getenv("GEOCODING_API_KEY");
    if (env_value == nullptr)
    {
        throw LocationFinderException("Missing API key");
    }
    geocoding_api_key = env_value;
}

std::string LocationFinder::create_geocoding_request_url(const std::string &address)
{
    std::string encoded_address = web_connector.url_safe_encode(address);
    return geocoding_api_url + "json?address=" + encoded_address + "&key=" + geocoding_api_key;
}

Location LocationFinder::parse_location_response(const std::string &response)
{
    Location location;

    JsonValue root = json_parser.parse(response);
    std::string response_status = root["status"].as_string();

    if (response_status == "OK")
    {
        JsonValue results = root["results"];
        JsonValue first_result = results[0];

        location.name = first_result["formatted_address"].as_string();
        location.latitude = first_result["geometry"]["location"]["lat"].as_double();
        location.longitude = first_result["geometry"]["location"]["lng"].as_double();
    }
    else if (response_status == "INVALID_REQUEST" || response_status == "ZERO_RESULTS")
    {
        throw InvalidAddressException("No Results Found. Please try again.");
    }
    else
    {
        throw ServerErrorException("Server Error. Please try again later.");
    }

    return location;
}

Location LocationFinder::find_location(const std::string &address)
{
    std::string request_url = create_geocoding_request_url(address);
    std::string response = web_connector.send_request(request_url);
    return parse_location_response(response);
}
