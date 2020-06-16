#ifndef SOCKETHELPER_H
#define SOCKETHELPER_H

#include "Service/ServerSocket.h"
#include "Messages/MessageType.h"
#include "Messages/RegisterMessage.h"
#include "Messages/ChatMessage.h"

class SocketHelper
{
private:
    ServerSocket socket;

    bool recvMeta(MetaData& meta);
    bool recvMessage(BaseMessage& message, MessageType type);

public:
    // void setup();
    void disconnect();
    bool tryConnect();
    bool isConnected();

    bool sendMessage(BaseMessage& message);
    bool recvChatMessage(BaseMessage& message);


};

#endif // SOCKETHELPER_H
