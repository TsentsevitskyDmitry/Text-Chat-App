#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <string>
#include <thread>
#include <functional>
#include "Service/SocketHelper.h"
#include "Messages/MessageTypes.h"
#include "Messages/RegisterMessage.h"

class ChatClient
{
private:
    SocketHelper helper;
    std::string clientName;
    std::thread* recvThread;
    std::function<void (string)> recvCallback;
    bool registered;

public:
    ChatClient() : recvThread(nullptr), registered(false) {}
    ~ChatClient();

    void disconnect();
    bool tryConnect();
    bool isRegistered();
    ErrorType tryRegister(std::string_view name);

    bool sendTextMessage(std::string_view text);

    bool recvTextMessage(std::string& text);
    void setTextMessageCallback(std::function<void(string)> callback);
};

#endif // CHATCLIENT_H
