#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include <winsock2.h>

class ClientInfo
{
private:
    SOCKET socket;

public:
    ClientInfo(SOCKET _socket) : socket(_socket) {}
    SOCKET getSocket() const;
};

#endif // CLIENTINFO_H
