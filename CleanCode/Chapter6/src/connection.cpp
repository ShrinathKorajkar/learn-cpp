
#include "connection.h"
#include <iostream>

bool Connection::initialiseSocketLibrary()
{
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        throw std::runtime_error("Error in initializing socket library");
    }
    return true;
}

SOCKET Connection::createSocket()
{
    SOCKET newSocket;
    newSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (newSocket == INVALID_SOCKET)
    {
        throw std::runtime_error("Error in creating socket");
    }
    return newSocket;
}

Connection::Connection() {}

Connection::~Connection()
{
    WSACleanup();
}