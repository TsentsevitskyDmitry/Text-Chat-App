#include <iostream>
#include "Controllers/ServerController.h"
#include "Controllers/StatusController.h"

using namespace std;


int main()
{
    cout << "Hello World!" << endl;

//    Settinsg s;
//    s.loadFromFile(".file");
//    ServerController::getInstance()->setup(s);

    ServerController server;

    auto statusController = [&server] () {
        StatusController status(&server);
        status.start(); // thread blocking
    };
    std::thread statusThread(statusController);

    server.start(); // thread blocking
    statusThread.join();

    return 0;
}
