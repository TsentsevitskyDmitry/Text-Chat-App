#ifndef STATUSCONTROLLER_H
#define STATUSCONTROLLER_H

#include "Service/pipehepler.h"
#include "Service/StatusPipe.h"
#include <iostream>
#include <functional>

#define SERVICE_NAME  _T("Text Chat App Server")

class StatusViewController
{
private:
    PipeHepler helper;
    std::function<void(ServerInfo&)> dataArrived;
    std::function<void(std::string&)> alertCallback;

    void alert(std::string text);

public:
    void updateButtonPressed();
    void installButtonPressed(std::wstring path);
    void removeButtonPressed();
    void stopButtonPressed();
    void startButtonPressed();

    void setDataArrivedCallback(std::function<void(ServerInfo&)> callback);
    void setAlertCallback(std::function<void(std::string&)> callback);
};

#endif // STATUSCONTROLLER_H
