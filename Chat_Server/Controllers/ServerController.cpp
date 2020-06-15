#include "ServerController.h"


ServerController* ServerController::getInstance()
{
    static ServerController* instance = nullptr;
    if (!instance){
        instance = new ServerController();
    }
    return instance;
}

void ServerController::start()
{
//    settings ??
//    server.setup();

    server.bindServerSocket();

    while(1){
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
    server.clean();
}
