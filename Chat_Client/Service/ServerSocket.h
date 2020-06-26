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
#include <string>
#include "Models/ConnectionSettings.h"
using namespace std;

class ServerSocket
{
private:
    std::string ip;
    std::string port;
    SOCKET connectSocket ;
    bool connected;

public:
    ServerSocket() : connected(false) {}
    ~ServerSocket();

    void setup(ConnectionSettings& settings);
    bool isConnected();
    bool tryConnect();
    void disconnect();

    bool sendRaw(char* data, size_t size);
    bool recvRaw(char* buff, size_t buffSize, size_t* recvBytes);

    static int getLastErrorCode();
};

#endif // CLIENTSOCHET_H
