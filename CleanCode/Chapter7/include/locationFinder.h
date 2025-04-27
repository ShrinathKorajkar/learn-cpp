#ifndef LOCATION_FINDER_H
#define LOCATION_FINDER_H

#include "jsonParser.h"
#include "webConnector.h"
#include <stdexcept>
#include <cstdlib>

/**
 * @brief Custom exception class for location finding errors.
 */
class LocationFinderException : public std::runtime_error
{
public:
    explicit LocationFinderException(const std::string &message)
        : std::runtime_error(message) {}
};

/**
 * @brief Custom exception class for invalid address errors.
 */
class InvalidAddressException : public LocationFinderException
{
public:
    explicit InvalidAddressException(const std::string &message)
        : LocationFinderException(message) {}
};

/**
 * @brief Custom exception class for server errors.
 */
class ServerErrorException : public LocationFinderException
{
public:
    explicit ServerErrorException(const std::string &message)
        : LocationFinderException(message) {}
};

struct Location
{
    std::string name;
    double latitude;
    double longitude;

    Location() : name(""), latitude(0), longitude(0) {}
};

/**
 * @brief Class responsible for finding location details using address.
 */
class LocationFinder
{
private:
    WebConnector &web_connector;
    JsonParser json_parser;
    std::string geocoding_api_url = "https://maps.googleapis.com/maps/api/geocode/";
    std::string geocoding_api_key;

    std::string create_geocoding_request_url(const std::string &address);
    Location parse_location_response(const std::string &response);

public:
    LocationFinder();
    ~LocationFinder() = default;

    /**
     * @brief Finds the location details based on the provided address.
     *
     * @param address The address for which location details are to be found.
     * @return Location The location details.
     * @throw InvalidAddressException If the provided address is invalid.
     * @throw ServerErrorException If there is an error while accessing the server.
     */
    Location find_location(const std::string &address);
};

#endif
