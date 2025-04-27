#include "networkProtocol.h"

#include <sstream>
#include <winsock2.h>

std::string NetworkProtocol::serializeRequest(const Request &request)
{
    std::ostringstream oss;
    oss << request.type << " ";
    switch (request.type)
    {
    case CARD_VALIDATION:
        oss << request.data.validationData.card.cardNumber
            << " " << request.data.validationData.card.expiryDate.day
            << " " << request.data.validationData.card.expiryDate.month
            << " " << request.data.validationData.card.expiryDate.year
            << " " << request.data.validationData.card.isBlocked
            << " " << request.data.validationData.card.noOfPinAttempts
            << " " << request.data.validationData.pin;
        break;
    case WITHDRAW:
        oss << request.data.withdrawData.accountNo
            << " " << request.data.withdrawData.amount;
        break;
    }
    return oss.str();
}

Request NetworkProtocol::deserializeRequest(const std::string &data)
{
    std::istringstream iss(data);
    Request request;
    int type;
    iss >> type;
    request.type = static_cast<RequestType>(type);
    switch (request.type)
    {
    case CARD_VALIDATION:
        iss >> request.data.validationData.card.cardNumber >> request.data.validationData.card.expiryDate.day >> request.data.validationData.card.expiryDate.month >> request.data.validationData.card.expiryDate.year >> request.data.validationData.card.isBlocked >> request.data.validationData.card.noOfPinAttempts >> request.data.validationData.pin;
        break;
    case WITHDRAW:
        iss >> request.data.withdrawData.accountNo >> request.data.withdrawData.amount;
        break;
    }
    return request;
}

std::string NetworkProtocol::serializeResponse(const Response &response)
{
    std::ostringstream oss;
    oss << response.status << " " << response.data;
    return oss.str();
}

Response NetworkProtocol::deserializeResponse(const std::string &responseString)
{
    Response response;
    std::istringstream iss(responseString);
    int status, data;
    iss >> status >> data;
    response.status = static_cast<ResponseStatus>(status);
    response.data = static_cast<int>(data);
    return response;
}

std::string NetworkProtocol::waitForIncommingMessage(const SOCKET &socket)
{
    char buffer[maxSizeOfMessage];

    int bytesRead = recv(socket, buffer, sizeof(buffer), 0);
    if (bytesRead == SOCKET_ERROR)
    {
        throw std::runtime_error("Server Down! Try again later");
    }
    buffer[bytesRead] = '\0';

    std::string message = buffer;

    return message;
}

Request NetworkProtocol::createWithdrawRequest(int accountNo, int amount)
{
    WithdrawData withdrawData;
    withdrawData.accountNo = accountNo;
    withdrawData.amount = amount;

    RequestData requestData;
    requestData.withdrawData = withdrawData;

    Request request;
    request.type = WITHDRAW;
    request.data = requestData;

    return request;
}

Request NetworkProtocol::createValidationRequest(Card *card, int pin)
{
    ValidationData validationData;
    validationData.card = *card;
    validationData.pin = pin;

    RequestData requestData;
    requestData.validationData = validationData;

    Request request;
    request.type = CARD_VALIDATION;
    request.data = requestData;

    return request;
}

bool NetworkProtocol::sendRequest(const Request &request, const SOCKET &clientSocket)
{
    std::string serializedRequest = serializeRequest(request);

    int bytesSent = send(clientSocket, serializedRequest.c_str(), serializedRequest.length(), 0);
    if (bytesSent == SOCKET_ERROR)
    {
        throw std::runtime_error("Unable to connect to server! Try again later");
    }
    return true;
}

bool NetworkProtocol::sendResponse(const Response &response, const SOCKET &clientSocket)
{
    std::string serializedResponse = serializeResponse(response);

    int bytesSent = send(clientSocket, serializedResponse.c_str(), serializedResponse.length(), 0);
    if (bytesSent == SOCKET_ERROR)
    {
        throw std::runtime_error("Error in sending message");
    }
    return true;
}

Response NetworkProtocol::waitForResponse(const SOCKET &clientSocket)
{
    std::string responseString = waitForIncommingMessage(clientSocket);
    Response response = deserializeResponse(responseString);
    return response;
}

Request NetworkProtocol::waitForRequest(const SOCKET &clientSocket)
{
    std::string requestString = waitForIncommingMessage(clientSocket);
    Request request = deserializeRequest(requestString);
    return request;
}
