#include "ClientProcessor.h"
#include <omp.h>

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

void ClientProcessor::broadcast(string &sender, ChatMessage &message)
{
    ChatMessage cm(sender + ": " + message.getData());
    server->lockClients();
    auto clients = server->getClients();
    int count = static_cast<int>(clients->size());

    omp_set_dynamic(0);
    omp_set_num_threads(count);
    #pragma omp parallel for
    for (int i = 0; i < count; i++) {
        const auto& [name, client] = *(std::next(clients->begin(), i));
        helper.sendMessage(cm, client);
    }

//    // Serial broadcst
//    for(const auto& [name, client] : *clients){
//        helper.sendMessage(cm, client);
//    }
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
