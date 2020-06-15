#ifndef CHATVIEWCONTROLLER_H
#define CHATVIEWCONTROLLER_H

#include "Service/ChatClient.h"

class ChatViewController
{
private:
    ChatClient chat;

public:
    ChatViewController();

    void testConnect();
    void testRegister(std::string_view name);
    void sendButtonClicked(std::string_view text);

};

#endif // CHATVIEWCONTROLLER_H
