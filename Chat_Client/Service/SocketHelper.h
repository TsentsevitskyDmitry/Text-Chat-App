#ifndef SOCKETHELPER_H
#define SOCKETHELPER_H

#include "Service/ServerSocket.h"
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

public:
    // void setup();
    void disconnect();
    bool tryConnect();
    bool isConnected();

    bool sendMessage(BaseMessage& message);
    bool recvChatMessage(BaseMessage& message);


};

#endif // SOCKETHELPER_H
