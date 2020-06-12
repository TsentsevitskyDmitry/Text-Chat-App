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

using namespace std;

#define DEFAULT_PORT "27015"

class ChatServer
{
private:
    SOCKET listenSocket;
    string port;

public:
//    ClientHandler();
//    ~ClientHandler();

    bool bindServerSocket();
    void clean();
    SOCKET acceptClient();
};

#endif // CHATSERVER_H
