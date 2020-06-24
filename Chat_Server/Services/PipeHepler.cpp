#include "PipeHepler.h"

bool PipeHepler::setStatus(ServerInfo& info)
{
    info.serialize();
    return pipe.write(info.getSerializedData(), info.getSerializedSize());
}

void PipeHepler::waitAndSend()
{
    pipe.waitClient();
    chat->lockClients();
    ServerInfo info(static_cast<uint32_t>(chat->getClients()->size()), chat->getRunnigPort());
//    ServerInfo info(228, 1337);
    chat->unlockClients();
    setStatus(info);
    pipe.close();
}

void PipeHepler::clean()
{
    pipe.close();
}
