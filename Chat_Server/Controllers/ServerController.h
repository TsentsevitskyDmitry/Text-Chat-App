#ifndef CHATPROCESSOR_H
#define CHATPROCESSOR_H

#include "Services/ChatServer.h"
#include "Services/ClientProcessor.h"
#include <thread>

class ServerController
{
private:
    ChatServer server;
    bool running;

public:
    ServerController() : running(false) {}
//    ~ServerController();

    bool isRunning();
    void setup(ServerConfig& config);
    void start();
    void stop();
    ChatServer* getChat();
};

#endif // CHATPROCESSOR_H
