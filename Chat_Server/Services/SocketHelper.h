#ifndef SOCKETHELPER_H
#define SOCKETHELPER_H

#include "Models/ClientInfo.h"
#include "Services/ClientSocket.h"
#include "Messages/MessageTypes.h"
#include "Messages/ErrorMessage.h"
#include "Messages/RegisterMessage.h"
#include "Messages/ChatMessage.h"
#include "Messages/MessageTypes.h"

class SocketHelper
{
private:
    ClientSocket socket;

    bool recvMeta(MetaData& meta);
    bool recvMessage(BaseMessage& message, MessageType type);
    bool recvRegistrationMessage(BaseMessage& message);

public:
    SocketHelper(SOCKET _socket) : socket(_socket) {}

    bool isClientConnected();
    void disconnect();

    bool sendMessage(BaseMessage& message, ClientInfo dest);
    bool sendMessage(BaseMessage&& message, ClientInfo dest);

    bool recvRegistrationName(std::string& name);
    bool recvChatMessage(BaseMessage& message);

};

#endif // SOCKETHELPER_H
