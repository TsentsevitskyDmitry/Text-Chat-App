#ifndef STATUSCONTROLLER_H
#define STATUSCONTROLLER_H

#include "Controllers/ServerController.h"
#include "Services/PipeHepler.h"

class StatusController
{
private:
    PipeHepler helper;
    bool running;

public:
    StatusController(ServerController* _controller) : helper(_controller->getChat()) {}

    bool isRunning();
    void start();
    void stop();
};

#endif // STATUSCONTROLLER_H
