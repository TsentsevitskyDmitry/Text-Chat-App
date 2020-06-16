#include "ClientProcessor.h"


ClientProcessor::~ClientProcessor()
{
    releaseClient();
}

void ClientProcessor::process()
{
    if(!registerClient()){
        cout << "Registration failed" << endl;
        return;
    }
    else{
        cout << "User '" << this->clientName << "' connected!" << endl;
    }


    while(helper.isClientConnected())
    {
        ChatMessage cm;
        if(!helper.recvChatMessage(cm)){
            return;
        }

        cout << clientName << ": " << cm.getData() << endl;
        broadcast(this->clientName, cm);
    }
}

void ClientProcessor::broadcast(string &sender, ChatMessage &message)
{
    ChatMessage cm(sender + ": " + message.getData());
    server->lockClients();
    auto clients = server->getClients();
    for(auto& [name, info] : *clients){
        helper.sendMessage(cm, info);
    }
    server->unlockClients();
}

bool ClientProcessor::registerClient()
{
    bool success = helper.recvRegistrationName(clientName);
    if(success){
        server->lockClients();
        auto clients = server->getClients();
        auto [pair, result] = clients->insert({clientName, info});
        success = result;
        server->unlockClients();
    }
    return success;
}

void ClientProcessor::releaseClient()
{
    server->lockClients();
    auto clients = server->getClients();
    clients->erase(clientName);
    server->unlockClients();
}
