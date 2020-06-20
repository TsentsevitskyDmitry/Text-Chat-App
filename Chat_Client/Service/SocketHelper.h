#ifndef SOCKETHELPER_H
#define SOCKETHELPER_H

#include "Service/ServerSocket.h"
#include "Messages/MessageTypes.h"
#include "Messages/ChatMessage.h"
#include "Messages/ErrorMessage.h"
#include "Messages/RegisterMessage.h"

class SocketHelper
{
private:
    ServerSocket socket;

    bool recvMeta(MetaData& meta);
    bool recvMessage(BaseMessage& message, MessageType type);

public:
    void setup(ConnectionSettings& settings);
    void disconnect();
    bool tryConnect();
    bool isConnected();

    bool sendMessage(BaseMessage& message);
    bool recvChatMessage(ChatMessage& message);
    bool recvErrorMessage(ErrorMessage& message);

    static int getSocketErrorCode();
};

#endif // SOCKETHELPER_H
