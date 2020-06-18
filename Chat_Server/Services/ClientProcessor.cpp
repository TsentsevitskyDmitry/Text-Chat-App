#include "ClientProcessor.h"


void ClientProcessor::process()
{
    if(!tyrRegister()){
        return;
    }

    ChatMessage cm;
    while(helper.isClientConnected() && helper.recvChatMessage(cm))
    {
        cout << clientName << ": " << cm.getData() << endl;
        broadcast(this->clientName, cm);
    }

    // Client disconected
    releaseClient();
}

bool ClientProcessor::tyrRegister()
{
    ErrorMessage error;
    if(!registerClient()){
        cout << "Registration failed" << endl;
        error.setError(ErrorType::NAME_ALREADY_USED_ERROR);
    }
    else{
        cout << "User '" << this->clientName << "' connected!" << endl;
        error.setError(ErrorType::NO_ERROR_ERROR);
    }
    helper.sendMessage(error, this->info);
    if(error.getError() == ErrorType::NAME_ALREADY_USED_ERROR){
        helper.disconnect();
        return false;
    }
    return true;
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
