#include "atmServer.h"

#include <iostream>

void ATMServer::init()
{
    initialiseSocketLibrary();
    clientSocket = createSocket();
}

ATMServer::ATMServer() : clientSocket(INVALID_SOCKET)
{
    init();
}

ATMServer::~ATMServer()
{
    if (clientSocket != INVALID_SOCKET)
    {
        closesocket(clientSocket);
    }
}

bool ATMServer::connectToServer()
{
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(serverIP.c_str());
    serverAddr.sin_port = htons(portNo);

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        throw std::runtime_error("Error in connecting to server");
    }
    return true;
}

bool ATMServer::withdrawCash(int accountNo, int amount)
{
    Request request = network.createWithdrawRequest(accountNo, amount);
    network.sendRequest(request, clientSocket);

    Response response = network.waitForResponse(clientSocket);
    if (response.status == INSUFFICIENT_BALANCE)
    {
        throw std::runtime_error("Insufficient Balance in Account");
    }

    return true;
}

int ATMServer::validateAccount(Card *card, int pin)
{
    Request request = network.createValidationRequest(card, pin);
    network.sendRequest(request, clientSocket);

    Response response = network.waitForResponse(clientSocket);
    if (response.status == BLOCKED)
    {
        throw std::runtime_error("Card is Blocked! contact your bank");
    }
    else if (response.status == INVALID_CARD)
    {
        throw std::runtime_error("Invaid Card! Use Appropriate Debit Card");
    }
    else if (response.status == INVALID_PIN)
    {
        throw std::runtime_error("Invaid Pin! Try Again");
    }

    return response.data;
}
