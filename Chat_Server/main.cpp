#include <iostream>
#include "Controllers/ServerController.h"
#include "Controllers/StatusController.h"
#include "Services/Settings.h"

using namespace std;


int main()
{
    cout << "running" << endl;



    ServerController server;
    StatusController status(&server);

    ServerConfig config;
    Settings::getConfig(config);
    server.setup(config);

    auto statusController = [&status] () {
        status.start(); // thread blocking
    };
    auto serverController = [&server] () {
        server.start(); // thread blocking
    };


    std::thread statusThread(statusController);
    std::thread serverThread(serverController);


    cin.get();
    cout << "here 2" << endl;

    status.stop();
    server.stop();

    cout << "here 3" << endl;


    statusThread.join();
    serverThread.join();

    return 0;
}
