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


void ServerInfo::serialize()
{
    if(serializedData){
        delete serializedData;
    }
    DataRepresentation data = {usersCount, runningPort};

    serializedSize = sizeof(data);
    serializedData = new char[serializedSize];
    memcpy(serializedData, &data, serializedSize);
}

char *ServerInfo::getSerializedData()
{
    return serializedData;
}

size_t ServerInfo::getSerializedSize()
{
    return serializedSize;
}
