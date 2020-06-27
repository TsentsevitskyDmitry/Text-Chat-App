#include "PipeHepler.h"
#include <iostream>

bool PipeHepler::getStatus(ServerInfo& info)
{
    bool res = status.open();
    if (!res) return false;
    const size_t buffSize = ServerInfo::getSerializedSize();
    char buff[buffSize];
    size_t recvBytes;
    status.read(buff, buffSize, &recvBytes);
    info.restore(buff, buffSize);
    status.close();
    return recvBytes;
}
