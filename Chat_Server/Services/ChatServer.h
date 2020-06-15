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
#include "Models/ClientInfo.h"

using namespace std;

#define DEFAULT_PORT "27015"

class ChatServer
{
private:
    SOCKET listenSocket;
    string port;
    std::mutex mutex;
    std::unordered_map<string, ClientInfo> clients;

public:
//    ChatServer();
    ~ChatServer();

    bool bindServerSocket();
    void clean();
    SOCKET acceptClient();

    void lockClients();
    std::unordered_map<string, ClientInfo>* getClients();
    void unlockClients();

};

#endif // CHATSERVER_H
