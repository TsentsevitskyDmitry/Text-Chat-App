#include "ChatViewController.h"

ChatViewController::ChatViewController()
{

}

void ChatViewController::sendButtonClicked(string_view text)
{

}

void ChatViewController::testConnect()
{
    chat.tryConnect();
}

void ChatViewController::testRegister()
{
    chat.tryRegister("nake");
}
