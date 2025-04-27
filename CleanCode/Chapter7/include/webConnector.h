#ifndef WEB_CONNECTOR_H
#define WEB_CONNECTOR_H

#include <curl/curl.h>
#include <stdexcept>

/**
 * @brief A custom exception class to handle web connector errors.
 */
class WebConnectorException : public std::runtime_error
{
public:
    explicit WebConnectorException(const std::string &message)
        : std::runtime_error(message) {}
};

/**
 * @brief Exception class for URL encoding errors.
 */
class UrlEncodeException : public WebConnectorException
{
public:
    explicit UrlEncodeException(const std::string &message)
        : WebConnectorException(message) {}
};

/**
 * @brief Exception class for request errors.
 */
class RequestException : public WebConnectorException
{
public:
    explicit RequestException(const std::string &message)
        : WebConnectorException(message) {}
};

/**
 * @brief A class for handling HTTP requests using libcurl.
 */
class WebConnector
{
private:
    CURL *curl = nullptr;      /**< Handle to CURL Library. */
    std::string response_data; /**< Stores response data. */

    /**
     * @brief Callback function for libcurl to write response data.
     *
     * @param contents Pointer to the data received.
     * @param size Size of each data element.
     * @param nmemb Number of elements.
     * @param output Pointer to the output string.
     * @return Size of the data written.
     */
    static size_t response_callback(void *contents, size_t size, size_t nmemb, std::string *output);

    /**
     * @brief Initializes the CURL library.
     *
     * @return True if initialization is successful, false otherwise.
     */
    bool initialize_curl();

    WebConnector();
    WebConnector(const WebConnector &) = delete;
    WebConnector &operator=(const WebConnector &) = delete;
    ~WebConnector();

public:
    /**
     * @brief Returns the singleton instance of WebConnector.
     *
     * @return Reference to the singleton instance.
     */
    static WebConnector &get_instance();

    /**
     * @brief Encodes a URL string to make it safe for use in a request.
     *
     * @param url The URL string to be encoded.
     * @return Encoded URL string.
     * @throw UrlEncodeException If there is an error during URL encoding.
     */
    std::string url_safe_encode(const std::string &url);

    /**
     * @brief Sends an HTTP request to the specified URL.
     *
     * @param url The URL to send the request to.
     * @return Response data received from the server.
     * @throw RequestException If there is an error during the request.
     */
    std::string send_request(const std::string &url);
};

#endif
