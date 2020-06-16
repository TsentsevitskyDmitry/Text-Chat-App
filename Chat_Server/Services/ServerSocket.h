#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <iostream>
#include "Messages/DataTypeMessage.h"
#include "Messages/ChatMessage.h"
#include "Models/ClientInfo.h"

using namespace std;

#define DEFAULT_BUFLEN 1024

class ServerSocket
{
private:
    SOCKET ClientSocket;
    bool clientConnected;

public:
    ServerSocket(SOCKET _socket) : ClientSocket(_socket), clientConnected(true) {}
    ~ServerSocket();

    bool isClientConnected();

    bool sendRaw(char* data, size_t size);
    bool sendRawTo(char* data, size_t size, SOCKET socket);
    bool recvRaw(char** buff, size_t* size);
    bool recvRawBytes(char** buff, size_t* size, size_t buffLen);
};

#endif // SERVERSOCKET_H
