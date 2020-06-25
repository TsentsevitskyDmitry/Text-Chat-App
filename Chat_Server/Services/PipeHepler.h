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

    void create();
    void waitAndSend();
    void close();
    void stop();
};

#endif // PIPEHEPLER_H
