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

public:
    void disconnect();
    void testConnect();
    void testRegister(std::string_view name);
    void sendButtonClicked(std::string_view text);

    void setTextMessageCallback(std::function<void(string)> callback);
    void setErrorMessageCallback(std::function<void(string)> callback);
};

#endif // CHATVIEWCONTROLLER_H
