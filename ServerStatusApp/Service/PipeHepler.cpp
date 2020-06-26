#include "PipeHepler.h"

bool PipeHepler::getStatus(ServerInfo& info)
{
    status.open();
    const size_t buffSize = ServerInfo::getSerializedSize();
    char buff[buffSize];
    size_t recvBytes;
    status.read(buff, buffSize, &recvBytes);
    info.restore(buff, buffSize);
    status.close();
    return recvBytes;
}
