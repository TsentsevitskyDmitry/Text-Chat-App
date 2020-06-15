#ifndef CLIENTPROCESSOR_H
#define CLIENTPROCESSOR_H

#include <winsock2.h>
#include <iostream>
#include "Services/ChatServer.h"
#include "Services/ClientHelper.h"
#include "Models/ClientInfo.h"

using namespace std;


class ClientProcessor
{
private:
    ClientInfo info;
    string clientName;
    ClientHelper helper;
    ChatServer* server;

    bool registerClient();
    void releaseClient();

public:
    ClientProcessor(ChatServer* _server, SOCKET _socket) : info(_socket), helper(_socket), server(_server) {}
    ~ClientProcessor();

    void process();

};

#endif // CLIENTPROCESSOR_H
