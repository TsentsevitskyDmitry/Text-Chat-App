#ifndef CHATSERVER_H
#define CHATSERVER_H
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <iostream>
#include <unordered_map>
#include <mutex>
#include "Models/ServerConfig.h"
#include "Models/ClientInfo.h"

using namespace std;

class ChatServer
{
private:
    SOCKET listenSocket;
    std::mutex mutex;
    std::unordered_map<string, ClientInfo> clients;
    ServerConfig config;

public:
    ChatServer() : config("27015") {}
    ~ChatServer();
    uint32_t getRunnigPort();

    bool bindServerSocket();
    SOCKET acceptClient();
    void clean();

    void lockClients();
    std::unordered_map<string, ClientInfo>* getClients();
    void unlockClients();

};

#endif // CHATSERVER_H
