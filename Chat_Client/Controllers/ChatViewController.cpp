#include "ChatViewController.h"

ChatClient *ChatViewController::getChat()
{
    return &chat;
}

void ChatViewController::disconnect()
{
    chat.disconnect();
}

void ChatViewController::tryConnect()
{
    chat.tryConnect();
}

void ChatViewController::tryRegister()
{
    ErrorType error =  chat.tryRegister();
    auto [result, description] = ErrorHelper::parseRegistrationError(error, chat.getClientName());
    reportError(description);
}

void ChatViewController::reportError(string_view error)
{
    if(errorMessageCallback){
        errorMessageCallback(string(error));
    }
}


void ChatViewController::sendButtonClicked(string_view text)
{
    if(!chat.sendTextMessage(text)){
     reportError(ErrorHelper::messageNotSent(text));
    }
}

void ChatViewController::setTextMessageCallback(std::function<void(string)> callback)
{
    chat.setTextMessageCallback(callback);
}

void ChatViewController::setErrorMessageCallback(std::function<void (string)> callback)
{
    errorMessageCallback = callback;
}
