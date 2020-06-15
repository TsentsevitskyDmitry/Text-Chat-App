#ifndef CLIENTHELPER_H
#define CLIENTHELPER_H

#include "Models/ClientInfo.h"
#include "Services/ServerSocket.h"
#include "Messages/DataTypeMessage.h"
#include "Messages/RegisterMessage.h"
#include "Messages/ChatMessage.h"
#include "Messages/MessageType.h"

class ClientHelper
{
private:
    ServerSocket socket;

    bool recvMessage(BaseMessage& message, size_t buffSize);
    bool recvTypedMessage(BaseMessage& message, MessageType type);
    bool recvDataTypeMessage(DataTypeMessage& message);
    bool recvRegistrationMessage(BaseMessage& message);

public:
    ClientHelper(SOCKET _socket) : socket(_socket) {}

    bool isClientConnected();

    bool sendMessage(BaseMessage& message, ClientInfo client);

    bool recvRegistrationName(std::string& name);
    bool recvChatMessage(BaseMessage& message);


};

#endif // CLIENTHELPER_H
