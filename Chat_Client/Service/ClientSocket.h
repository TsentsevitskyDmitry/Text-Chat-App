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

#include "Messages/DataTypeMessage.h"
#include "Messages/ChatMessage.h"

using namespace std;

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 1024


class ClientSocket
{
private:
    SOCKET ConnectSocket;

public:
    ~ClientSocket();

//    void setup();
    bool try_connect();
    void disconnect();
    bool sendRaw(char* data, size_t size);

};

#endif // CLIENTSOCHET_H
