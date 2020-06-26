#ifndef SOCKETHELPER_H
#define SOCKETHELPER_H

#include "Services/ClientSocket.h"
#include "Messages/MessageTypes.h"
#include "Messages/ErrorMessage.h"
#include "Messages/RegisterMessage.h"
#include "Messages/ChatMessage.h"
#include "Messages/MessageTypes.h"

class SocketHelper
{
private:
    ClientSocket clientSocket;

    bool recvMeta(MetaData& meta);
    bool recvMessage(BaseMessage& message, MessageType type);
    bool recvRegistrationMessage(BaseMessage& message);

public:
    SocketHelper(SOCKET _clientSocket) : clientSocket(_clientSocket) {}

    bool isClientConnected();
    void disconnect();

    bool sendMessage(BaseMessage& message);
    bool sendMessage(BaseMessage&& message);

    bool sendSerializedMessage(BaseMessage& message);
    bool sendSerializedMessage(BaseMessage&& message);

    bool recvRegistrationName(std::string& name);
    bool recvChatMessage(BaseMessage& message);

};

#endif // SOCKETHELPER_H
