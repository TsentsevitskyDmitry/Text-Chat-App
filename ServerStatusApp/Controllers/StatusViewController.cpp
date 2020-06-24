#include "StatusViewController.h"

void StatusViewController::updateButtonPressed()
{
    ServerInfo info;
    helper.getStatus(info);
    if(dataArrived){
        dataArrived(info);
    }
}

void StatusViewController::setDataArrivedCallback(std::function<void (ServerInfo &)> callback)
{
    dataArrived = callback;
}
