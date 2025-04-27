#ifndef __SOCKET_CONNECTION_H__
#define __SOCKET_CONNECTION_H

#include <winsock2.h>
#include <ws2tcpip.h>

class Connection
{
private:
    WSADATA wsaData;

protected:
    bool initialiseSocketLibrary();

    SOCKET createSocket();

public:
    Connection();

    ~Connection();
};

#endif