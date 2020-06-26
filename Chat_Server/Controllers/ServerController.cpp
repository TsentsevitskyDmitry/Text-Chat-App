#include "ServerController.h"

bool ServerController::isRunning()
{
    return running;
}

void ServerController::setup(ServerConfig &config)
{
    server.setup(config);
}

void ServerController::start()
{
    running = true;
    if(!server.bindServerSocket()){
        return;
    }

    while(running){
        SOCKET clientSocket = server.acceptClient();
        //
        auto processor = [this] (SOCKET clientSocket) {
            cout << "Client connected" << endl;
            ClientProcessor p(&server, clientSocket);
            p.process();
            cout << "Client processed" << endl;
        };

        std::thread thread(processor,clientSocket);
        thread.detach();
    }
}

void ServerController::stop()
{
    running = false;
    server.clean();
}

ChatServer *ServerController::getChat()
{
    return &server;
}
