#include "ChatClient.h"

ChatClient::~ChatClient()
{
    disconnect();
    recvThread->join();
}

void ChatClient::disconnect()
{
    registered = false;;
    helper.disconnect();
}

bool ChatClient::tryConnect()
{
    return helper.tryConnect();
}

bool ChatClient::isRegistered()
{
    return registered;
}

ErrorType ChatClient::tryRegister(std::string_view name)
{
    if(name.length() < 1){
        return ErrorType::INTERNAL_ERROR;
    }
    clientName = name;
    RegisterMessage rm(name);
    helper.sendMessage(rm);
    ErrorMessage error;
    helper.recvErrorMessage(error);
    if (error.getError() == ErrorType::NO_ERROR_ERROR){
        registered = true;
    }
    return error.getError();
}

bool ChatClient::sendTextMessage(std::string_view text)
{
    ChatMessage cm(text);
    return helper.sendMessage(cm);
}

bool ChatClient::recvTextMessage(string &text)
{
    ChatMessage cm;
    if(!helper.recvChatMessage(cm)){
        return false;
    }
    text = cm.getData();
    return true;
}

void ChatClient::setTextMessageCallback(std::function<void (string)> callback)
{
    recvCallbackFunction = callback;
    if(recvThread)
        return;

    auto worker = [this] () {
        while(!isRegistered()){
            std::this_thread::sleep_for(100ms);
        }
        while (helper.isConnected()){
            string text;
            if(recvTextMessage(text) && recvCallbackFunction){
                cout << "got: " << text << endl;
                recvCallbackFunction(text);
            }
        }
    };
    recvThread = new thread(worker);
}
