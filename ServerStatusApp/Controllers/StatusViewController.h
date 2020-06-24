#ifndef STATUSCONTROLLER_H
#define STATUSCONTROLLER_H

#include "Service/pipehepler.h"
#include "Service/StatusPipe.h"
#include <iostream>
#include <functional>

class StatusViewController
{
private:
    PipeHepler helper;
    std::function<void(ServerInfo&)> dataArrived;

public:
    void updateButtonPressed();
    void installButtonPressed();
    void removeButtonPressed();
    void startButtonPressed();

    void setDataArrivedCallback(std::function<void(ServerInfo&)> callback);
};

#endif // STATUSCONTROLLER_H
