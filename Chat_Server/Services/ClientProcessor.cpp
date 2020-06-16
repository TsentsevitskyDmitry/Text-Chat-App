#include "ClientProcessor.h"


ClientProcessor::~ClientProcessor()
{
    releaseClient();
}

void ClientProcessor::process()
{
    if(!registerClient()){
        cout << "user already exist" << endl;
        return;
    }
    else{
        cout << "done!!!" << endl;
    }


    while(helper.isClientConnected())
    {
        ChatMessage cm;
        if(!helper.recvChatMessage(cm)){
            return;
        }

        cout << clientName << ": " << cm.getData() << endl;
        broadcast(this->clientName, cm);
//        helper.sendMessage(cm, this->info);

    }
}


void ClientProcessor::broadcast(string &sender, ChatMessage &message)
{
    ChatMessage cm(sender + ": " + message.getData());
    server->lockClients();
    auto clients = server->getClients();
    for(auto [name, info] : *clients){
//        cout << info.getSocket() << " " << this->info.getSocket() << endl;
        helper.sendMessage(cm, info);
//        helper.sendMessage(cm, this->info);
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
