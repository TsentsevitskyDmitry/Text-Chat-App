#include "ChatViewController.h"


void ChatViewController::disconnect()
{
    chat.disconnect();
}

void ChatViewController::testConnect()
{
    chat.tryConnect();
}

void ChatViewController::testRegister(std::string_view name)
{
    chat.tryRegister(name);
}

void ChatViewController::sendButtonClicked(string_view text)
{
    chat.sendTextMessage(text);
}

void ChatViewController::setTextMessageCallback(std::function<void(string)> callback)
{
    chat.setTextMessageCallback(callback);
}
