#ifndef SOCKETHELPER_H
#define SOCKETHELPER_H

#include "Models/ClientInfo.h"
#include "Services/ServerSocket.h"
#include "Messages/DataTypeMessage.h"
#include "Messages/RegisterMessage.h"
#include "Messages/ChatMessage.h"
#include "Messages/MessageType.h"

class SocketHelper
{
private:
    ServerSocket socket;

    bool recvMessage(BaseMessage& message, size_t buffSize);
    bool recvTypedMessage(BaseMessage& message, MessageType type);
    bool recvDataTypeMessage(DataTypeMessage& message);
    bool recvRegistrationMessage(BaseMessage& message);

public:
    SocketHelper(SOCKET _socket) : socket(_socket) {}

    bool isClientConnected();

    bool sendMessage(BaseMessage& message, ClientInfo client);

    bool recvRegistrationName(std::string& name);
    bool recvChatMessage(BaseMessage& message);


};

#endif // SOCKETHELPER_H
