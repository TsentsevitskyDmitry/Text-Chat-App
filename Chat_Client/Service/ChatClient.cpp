#include "ChatClient.h"

ChatClient::~ChatClient()
{
    recvThread->join();
}

void ChatClient::disconnect()
{
    helper.disconnect();
}

bool ChatClient::tryConnect()
{
    return helper.tryConnect();
}

bool ChatClient::tryRegister(std::string_view name)
{
    if(name.length() < 1){
        return false;
    }
    clientName = name;
    RegisterMessage rm(name);
    return helper.sendMessage(rm);
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
    recvCallback = callback;
    if(recvThread)
        return;

    auto worker = [this] () {
        while (helper.isConnected()){
            string text;
            if(recvTextMessage(text) || recvCallback){
             recvCallback(text);
            }
        }
    };
    recvThread = new thread(worker);
}
