#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <string>
#include "Service/ClientSocket.h"
#include "Messages/MessageType.h"
#include "Messages/DataTypeMessage.h"
#include "Messages/RegisterMessage.h"

class ChatClient
{
private:
    ClientSocket socket;
    std::string clientName;
    bool send(BaseMessage& message);

public:
    bool tryConnect();
    bool tryRegister(std::string_view name);
    bool sendTextMessage(std::string_view text);
};

#endif // CHATCLIENT_H
