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
    ErrorType error =  chat.tryRegister(name);
    auto [result, description] = ErrorHelper::parseRegistrationError(error, name);
    if(errorMessageCallback){
        errorMessageCallback(description);
    }

}

void ChatViewController::sendButtonClicked(string_view text)
{
    chat.sendTextMessage(text);
}

void ChatViewController::setTextMessageCallback(std::function<void(string)> callback)
{
    chat.setTextMessageCallback(callback);
}

void ChatViewController::setErrorMessageCallback(std::function<void (string)> callback)
{
    errorMessageCallback = callback;
}
