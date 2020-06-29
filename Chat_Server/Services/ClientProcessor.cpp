#include "ClientProcessor.h"
#include <omp.h>

void ClientProcessor::process()
{
    if(!tyrRegister()){
        return;
    }

    // User connected
    broadcast(ChatMessage("User '" + this->clientName + "' connected!", "Server"));

    ChatMessage cm;
    while(helper.isClientConnected() && helper.recvChatMessage(cm))
    {
        broadcast(cm);
    }

    // User disconected
    broadcast(ChatMessage("User '" + this->clientName + "' disconected!", "Server"));

    // Client disconected
    releaseClient();
}

void ClientProcessor::broadcast(ChatMessage &message)
{
    message.serialize();
    server->lockClients();
    auto clients = server->getClients();
    int count = static_cast<int>(clients->size());

    // *due to my benchmarking, needs serious testing*
    // Thread sync overhead is greater than serial sending time in small queues.
    // Parallel broadcasting will be useful only with a large number of clients.
    // This is because send() func executes very fast.
    // OpenMP gives even more overhead (because threads are created and destroyed more than once),
    // but is used for portability and simplification of code.
    if(count >= 100) {
        // Use OpenMP
        omp_set_dynamic(0);
        omp_set_num_threads(count);
        #pragma omp parallel for
        for(int i = 0; i < count; ++i){
            auto& [name, client] = *(std::next(clients->begin(), i));
             client.getHelper()->sendSerializedMessage(message);
        }
    }
    else {
        // Serial broadcst
        for(auto& [name, client] : *clients){
            client.getHelper()->sendSerializedMessage(message);
        }
    }

    server->unlockClients();
}               

void ClientProcessor::broadcast(ChatMessage&& message)
{
    broadcast(message);
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
