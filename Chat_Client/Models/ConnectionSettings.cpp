#include "ConnectionSettings.h"

const char *ConnectionSettings::getIp()
{
    return ip.c_str();
}

const char *ConnectionSettings::getPort()
{
    return port.c_str();
}

std::string ConnectionSettings::getName()
{
    return name;
}
