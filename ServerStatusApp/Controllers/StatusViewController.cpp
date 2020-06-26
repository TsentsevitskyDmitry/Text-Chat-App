#include "StatusViewController.h"

void StatusViewController::updateButtonPressed()
{
    ServerInfo info;
    helper.getStatus(info);
    if(dataArrived){
        dataArrived(info);
    }
}

void StatusViewController::installButtonPressed(std::string path)
{

}

void StatusViewController::removeButtonPressed()
{

}

void StatusViewController::startButtonPressed()
{

}

void StatusViewController::setDataArrivedCallback(std::function<void (ServerInfo &)> callback)
{
    dataArrived = callback;
}
