#include "ChatViewController.h"

ChatClient *ChatViewController::getChat()
{
    return &chat;
}

void ChatViewController::disconnect()
{
    chat.disconnect();
}

bool ChatViewController::tryConnect()
{
    return chat.tryConnect();
}

bool ChatViewController::tryRegister()
{
    ErrorType error =  chat.tryRegister();
    auto [result, description] = ErrorHelper::parseRegistrationError(error, chat.getClientName());
    reportError(description);
    return result;
}

void ChatViewController::reportError(string_view error)
{
    if(errorMessageCallback){
        errorMessageCallback(string(error));
    }
}


void ChatViewController::sendButtonClicked(string_view text)
{
    if(!text.length()){
        return;
    }
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
    chat.setErrorMessageCallback(callback);
}
