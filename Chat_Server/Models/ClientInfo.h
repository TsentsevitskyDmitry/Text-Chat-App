#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include "Services/SocketHelper.h"

class ClientInfo
{
private:
    SocketHelper* helper;

public:
    ClientInfo(SocketHelper*  _helper) : helper(_helper) {}
    SocketHelper* getHelper();
};

#endif // CLIENTINFO_H
