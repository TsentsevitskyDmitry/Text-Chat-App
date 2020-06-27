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
    ConnectionSettings settings;
    std::thread* recvThread;
    std::function<void (string)> recvCallbackFunction;
    std::function<void (string)> errorCallbackFunction;
    bool registered;

    void startRecv();

public:
    ChatClient() : recvThread(nullptr), registered(false) {}
    ~ChatClient();

    void setup(ConnectionSettings settings);
    void disconnect();
    bool tryConnect();
    bool isConnected();
    bool isRegistered();
    ErrorType tryRegister();

    bool sendTextMessage(std::string_view text);

    bool recvTextMessage(string &text, string &sender);
    void setTextMessageCallback(std::function<void(string)> callback);
    void setErrorMessageCallback(std::function<void(string)> callback);

    std::string getClientName();
};

#endif // CHATCLIENT_H
