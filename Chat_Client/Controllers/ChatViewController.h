#ifndef CHATVIEWCONTROLLER_H
#define CHATVIEWCONTROLLER_H

#include "Service/ChatClient.h"

class ChatViewController
{
private:
    ChatClient chat;

public:
    ChatViewController();

    void sendButtonClicked(std::string_view text);
    void testConnect();
    void testRegister();
};

#endif // CHATVIEWCONTROLLER_H
