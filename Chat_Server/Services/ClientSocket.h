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
#include "Messages/ChatMessage.h"

using namespace std;

#define DEFAULT_BUFLEN 1024

class ClientSocket
{
private:
    SOCKET clientSocket;
    bool clientConnected;

public:
    ClientSocket(SOCKET _socket) : clientSocket(_socket), clientConnected(true) {}
    ~ClientSocket();

    bool isClientConnected();
    void disconnect();

    bool sendRaw(char* data, size_t size);
    bool sendRawTo(char* data, size_t size, SOCKET socket);
    bool recvRaw(char* buff, size_t buffSize, size_t* recvBytes);
};

#endif // SERVERSOCKET_H
