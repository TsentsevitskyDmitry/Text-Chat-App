#ifndef PIPEHEPLER_H
#define PIPEHEPLER_H

#include "Services/ChatServer.h"
#include "Services/StatusPipe.h"
#include "Models/ServerInfo.h"

class PipeHepler
{
private:
    ChatServer *chat;
    StatusPipe pipe;
    bool setStatus(ServerInfo& info);

public:
    PipeHepler(ChatServer* _chat) : chat(_chat) {}

    void waitAndSend();
    void clean();
};

#endif // PIPEHEPLER_H
