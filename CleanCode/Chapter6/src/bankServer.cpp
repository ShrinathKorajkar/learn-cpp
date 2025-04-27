
#include "bankServer.h"

bool BankServer::bindSocketToHost()
{
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(portNo);
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        throw std::runtime_error("Error binding socket to host");
    }
    return true;
}

bool BankServer::listenIncomingConnections()
{
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        throw std::runtime_error("Error listening on socket");
    }
    return true;
}

bool BankServer::acceptIncomingConnection()
{
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientSocket == INVALID_SOCKET)
    {
        throw std::runtime_error("Error in accepting connection");
    }
    return true;
}

BankServer::BankServer() : serverSocket(INVALID_SOCKET), clientSocket(INVALID_SOCKET)
{
    initialiseSocketLibrary();
    serverSocket = createSocket();
    bindSocketToHost();
}

BankServer::~BankServer()
{
    if (clientSocket != INVALID_SOCKET)
    {
        closesocket(clientSocket);
    }

    if (serverSocket != INVALID_SOCKET)
    {
        closesocket(serverSocket);
    }
}

void BankServer::start()
{
    listenIncomingConnections();
    acceptIncomingConnection();
}

Request BankServer::getNextRequest()
{
    return network.waitForRequest(clientSocket);
}

bool BankServer::sendResponseToClient(Response &response)
{
    return network.sendResponse(response, clientSocket);
}
