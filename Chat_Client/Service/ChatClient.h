#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <string>
#include <thread>
#include <functional>
#include "Service/SocketHelper.h"
#include "Messages/MessageType.h"
#include "Messages/RegisterMessage.h"

class ChatClient
{
private:
    SocketHelper helper;
    std::string clientName;
    std::thread* recvThread;
    std::function<void (string)> recvCallback;

public:
    ChatClient() : recvThread(nullptr) {}
    ~ChatClient();

    void disconnect();
    bool tryConnect();
    bool tryRegister(std::string_view name);

    bool sendTextMessage(std::string_view text);

    bool recvTextMessage(std::string& text);
    void setTextMessageCallback(std::function<void(string)> callback);
};

#endif // CHATCLIENT_H
