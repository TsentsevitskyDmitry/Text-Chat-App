#include "ChatViewController.h"

ChatViewController::ChatViewController()
{

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
