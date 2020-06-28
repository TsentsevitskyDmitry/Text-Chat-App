#ifndef CLIENTPROCESSOR_H
#define CLIENTPROCESSOR_H

#include <winsock2.h>
#include <iostream>
#include "Services/ChatServer.h"
#include "Services/SocketHelper.h"
#include "Models/ClientInfo.h"

using namespace std;


class ClientProcessor
{
private:
    ChatServer* server;
    SocketHelper helper;
    ClientInfo info;
    string clientName;

    bool tyrRegister();
    bool registerClient();
    void releaseClient();
    void broadcast(ChatMessage& message);
    void broadcast(ChatMessage&& message);

public:
    ClientProcessor(ChatServer* _server, SOCKET _socket) : server(_server), helper(_socket), info(&helper) {}

    void process();

};

#endif // CLIENTPROCESSOR_H
