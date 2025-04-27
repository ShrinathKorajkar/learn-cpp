#ifndef __NETWORK_PROTOCOLS_H__
#define __NETWORK_PROTOCOLS_H__

#include "networkMsgs.h"

#include <winsock2.h>

class NetworkProtocol
{
private:
    int maxSizeOfMessage = 1024;

    std::string serializeRequest(const Request &request);

    Request deserializeRequest(const std::string &data);

    std::string serializeResponse(const Response &response);

    Response deserializeResponse(const std::string &responseString);

    std::string waitForIncommingMessage(const SOCKET &socket);

public:
    Request createWithdrawRequest(int accountNo, int amount);

    Request createValidationRequest(Card *card, int pin);

    bool sendRequest(const Request &request, const SOCKET &clientSocket);

    bool sendResponse(const Response &response, const SOCKET &clientSocket);

    Response waitForResponse(const SOCKET &clientSocket);

    Request waitForRequest(const SOCKET &clientSocket);
};

#endif