#ifndef CLIENTPROCESSOR_H
#define CLIENTPROCESSOR_H

#include <winsock2.h>
#include <iostream>
#include "Services/ServerSocket.h"
#include "Messages/ServiceMessage.h"
#include "Messages/RegisterMessage.h"
#include "Messages/ChatMessage.h"
#include "Messages/messagetypes.h"
#include "Models/ClientInfo.h"

using namespace std;


class ClientProcessor
{
private:
    ServerSocket socket;
    ClientInfo info;

    bool sendMessage(BaseMessage& message);
    bool recvMessage(BaseMessage& message, size_t buffSize);
    bool recvServiceMessage(ServiceMessage& message);

    bool registerClient(ClientInfo& info);
    bool releaseClient(ClientInfo& info);


public:
    ClientProcessor(SOCKET _socket) : socket(_socket) {}
    void process();

};

#endif // CLIENTPROCESSOR_H
