#include "ClientProcessor.h"

#define TIME_COST(code) { \
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now(); \
    code; \
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);\
    std::cout << time.count() << "mc" << std::endl; }\

void ClientProcessor::process()
{
    if(!tyrRegister()){
        return;
    }

    ChatMessage cm;
    while(helper.isClientConnected() && helper.recvChatMessage(cm))
    {
        cout << clientName << ": " << cm.getData() << endl;
        TIME_COST(broadcast(this->clientName, cm););
//        broadcast(this->clientName, cm);
    }

    // Client disconected
    releaseClient();
}

void ClientProcessor::broadcast(string &sender, ChatMessage &message)
{
    ChatMessage cm(sender + ": " + message.getData());
    server->lockClients();
    auto clients = server->getClients();

    // Serial broadcst
    for(const auto& [name, client] : *clients){
        helper.sendMessage(cm, client);
    }
    server->unlockClients();
}

bool ClientProcessor::tyrRegister()
{
    if(!registerClient()){
        cout << "Registration failed" << endl;
        helper.sendMessage(ErrorMessage(ErrorType::NAME_ALREADY_USED_ERROR), this->info);
        helper.disconnect();
        return false;
    }
    else{
        cout << "User '" << this->clientName << "' connected!" << endl;
        helper.sendMessage(ErrorMessage(ErrorType::NO_ERROR_ERROR), this->info);
    }
    return true;
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
