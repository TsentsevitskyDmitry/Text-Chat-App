#ifndef CHATVIEWCONTROLLER_H
#define CHATVIEWCONTROLLER_H

#include "Service/ChatClient.h"
#include <functional>

class ChatViewController
{
private:
    ChatClient chat;

public:
    void disconnect();
    void testConnect();
    void testRegister(std::string_view name);
    void sendButtonClicked(std::string_view text);

    void setTextMessageCallback(std::function<void(string)> callback);
};

#endif // CHATVIEWCONTROLLER_H
