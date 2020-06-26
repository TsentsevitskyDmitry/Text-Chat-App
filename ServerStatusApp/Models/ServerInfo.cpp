#include "ServerInfo.h"


uint32_t ServerInfo::getRunningPort() const
{
    return runningPort;
}

void ServerInfo::setRunningPort(const uint32_t &value)
{
    runningPort = value;
}

uint32_t ServerInfo::getUsersCount() const
{
    return usersCount;
}

void ServerInfo::setUsersCount(const uint32_t &value)
{
    usersCount = value;
}

bool ServerInfo::restore(char *data, size_t size)
{
    ServerInfoDataRepresentation _data;
    memcpy(&_data, data, size);
    this->usersCount = _data.val1;
    this->runningPort = _data.val2;
    return true;
}
