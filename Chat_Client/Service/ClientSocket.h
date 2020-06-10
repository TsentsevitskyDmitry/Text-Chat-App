#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 1024


class ClientSocket
{
private:
public:
    void try_connect();
};
