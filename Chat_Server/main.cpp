#include <iostream>
#include "Controllers/ServerController.h"

using namespace std;


int main()
{
    cout << "Hello World!" << endl;

//    Settinsg s;
//    s.loadFromFile(".file");
//    ServerController::getInstance()->setup(s);

    ServerController::getInstance()->start();

//    auto remoteController = [] () {
//        RemoteController r;
//        r.listen();
//    };
//    std::thread t(remoteController);
//    t.join();

    return 0;
}
