#include "ClientProcessor.h"
#include <omp.h>
#include <vector>
#include <thread>

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
    cm.serialize();
    server->lockClients();
    auto clients = server->getClients();
    int count = static_cast<int>(clients->size());

    if(count >= 100) {
        // Use OpenMP
        omp_set_dynamic(0);
        omp_set_num_threads(count);
        #pragma omp parallel for
        for(int i = 0; i < count; ++i){
            auto& [name, client] = *(std::next(clients->begin(), i));
             client.getHelper()->sendSerializedMessage(cm);
        }
    }
    else {
        // Serial broadcst
        for(auto& [name, client] : *clients){
            client.getHelper()->sendSerializedMessage(cm);
        }
    }

    server->unlockClients();
}               

bool ClientProcessor::tyrRegister()
{
    if(!registerClient()){
        cout << "Registration failed" << endl;
        helper.sendMessage(ErrorMessage(ErrorType::NAME_ALREADY_USED_ERROR));
        helper.disconnect();
        return false;
    }
    else{
        cout << "User '" << this->clientName << "' connected!" << endl;
        helper.sendMessage(ErrorMessage(ErrorType::NO_ERROR_ERROR));
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
