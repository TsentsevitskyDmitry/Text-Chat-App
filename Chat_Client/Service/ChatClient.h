#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <string>
#include "Service/ClientSocket.h"
#include "Messages/messagetypes.h"
#include "Messages/ServiceMessage.h"
#include "Messages/RegisterMessage.h"

class ChatClient
{
private:
    ClientSocket socket;
    bool send(BaseMessage& message);

public:
    bool tryConnect();
    bool tryRegister(std::string name);
};

#endif // CHATCLIENT_H
