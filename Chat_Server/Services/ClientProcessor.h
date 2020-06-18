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
    ClientInfo info;
    string clientName;
    SocketHelper helper;
    ChatServer* server;

    bool tyrRegister();
    bool registerClient();
    void releaseClient();
    void broadcast(std::string& sender, ChatMessage& message);

public:
    ClientProcessor(ChatServer* _server, SOCKET _socket) : info(_socket), helper(_socket), server(_server) {}

    void process();

};

#endif // CLIENTPROCESSOR_H
