#ifndef __ATM_SERVER_H__
#define __ATM_SERVER_H__

#include "connection.h"
#include "networkProtocol.h"

class ATMServer : protected Connection
{
private:
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    std::string serverIP = "127.0.0.1";
    int portNo = 8080;
    NetworkProtocol network;

    void init();

public:
    ATMServer();

    ~ATMServer();

    bool connectToServer();

    bool withdrawCash(int accountNo, int amount);

    int validateAccount(Card *card, int pin);
};

#endif