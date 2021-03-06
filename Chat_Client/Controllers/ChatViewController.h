#ifndef CHATVIEWCONTROLLER_H
#define CHATVIEWCONTROLLER_H

#include <functional>
#include "Service/ChatClient.h"
#include "Service/ErrorHelper.h"

class ChatViewController
{
private:
    ChatClient chat;
    std::function<void(string)> errorMessageCallback;
    void reportError(std::string_view error);
    void removePrefix(string_view& text);
    void removePostfix(string_view& text);

public:
    ChatClient* getChat();

    void disconnect();
    bool tryConnect();
    bool tryRegister();
    void sendButtonClicked(std::string_view text);

    void setTextMessageCallback(std::function<void(string)> callback);
    void setErrorMessageCallback(std::function<void(string)> callback);
};

#endif // CHATVIEWCONTROLLER_H
