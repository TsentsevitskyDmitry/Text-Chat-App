#ifndef CLIENTSOCHET_H
#define CLIENTSOCHET_H

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

#define DEFAULT_PORT "27015"

class ServerSocket
{
private:
    SOCKET connectSocket ;
    bool connected;

public:
    ServerSocket() : connected(false) {}
    ~ServerSocket();

//    void setup();
    bool isConnected();
    bool tryConnect();
    void disconnect();

    bool sendRaw(char* data, size_t size);
    bool recvRaw(char* buff, size_t* size, size_t buffSize);

    static int getLastErrorCode();
};

#endif // CLIENTSOCHET_H
