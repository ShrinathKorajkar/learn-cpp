#ifndef __BANK_SERVER_H__
#define __BANK_SERVER_H__

#include "connection.h"
#include "networkProtocol.h"
#include <winsock2.h>
#include <ws2tcpip.h>

class BankServer : protected Connection
{
private:
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    NetworkProtocol network;
    int portNo = 8080;

    bool bindSocketToHost();

    bool listenIncomingConnections();

    bool acceptIncomingConnection();

public:
    BankServer();

    ~BankServer();

    void start();

    Request getNextRequest();

    bool sendResponseToClient(Response &response);
};

#endif