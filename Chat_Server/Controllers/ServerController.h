#ifndef CHATPROCESSOR_H
#define CHATPROCESSOR_H

#include "Services/ChatServer.h"
#include "Services/ClientProcessor.h"
#include <thread>

class ServerController
{
private:
    static ServerController* instance;
    ChatServer server;

public:
//    ServerController();
//    ~ServerController();

    static ServerController* getInstance();
    void start();
    void stop();
};

#endif // CHATPROCESSOR_H
