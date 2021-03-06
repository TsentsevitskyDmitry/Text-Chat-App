#include "ChatClient.h"

ChatClient::~ChatClient()
{
    disconnect();
}

void ChatClient::setup(ConnectionSettings settings)
{
    this->settings = settings;
    helper.setup(settings);
}

void ChatClient::disconnect()
{
    registered = false;;
    helper.disconnect();
    if(recvThread){
        recvThread->join();
    }
}

bool ChatClient::tryConnect()
{
    disconnect();
    return helper.tryConnect();
}

bool ChatClient::isConnected()
{
    return helper.isConnected();
}

bool ChatClient::isRegistered()
{
    return registered;
}

ErrorType ChatClient::tryRegister()
{
    registered = false;
    if(settings.getName().length() < 1){
        helper.disconnect();
        return ErrorType::INTERNAL_ERROR;
    }
    RegisterMessage rm(settings.getName());
    helper.sendMessage(rm);
    ErrorMessage error;
    helper.recvErrorMessage(error);
    if (error.getError() == ErrorType::NO_ERROR_ERROR){
        registered = true;
    }
    startRecv();
    return error.getError();
}

void ChatClient::startRecv()
{
    if(recvThread){
        if(recvThread->joinable()){
            return;
        }
    }


    auto worker = [this] () {
        while (isRegistered() && helper.isConnected()){
            string text, sender;
            if(recvTextMessage(text ,sender) && recvCallbackFunction){
                recvCallbackFunction(sender + ": " + text);
            }
            else if (isRegistered() && errorCallbackFunction){
                errorCallbackFunction("Server error.");
            }
        }
    };
    recvThread = new thread(worker);
}

bool ChatClient::sendTextMessage(std::string_view text)
{
    ChatMessage cm(text, settings.getName());
    return helper.sendMessage(cm);
}

bool ChatClient::recvTextMessage(string &text, string &sender)
{
    ChatMessage cm;
    if(!helper.recvChatMessage(cm)){
        return false;
    }
    text = cm.getData();
    sender = cm.getSender();
    return true;
}

void ChatClient::setTextMessageCallback(std::function<void (string)> callback)
{
    recvCallbackFunction = callback;
}

void ChatClient::setErrorMessageCallback(std::function<void (string)> callback)
{
    errorCallbackFunction = callback;
}

string ChatClient::getClientName()
{
    return settings.getName();
}
