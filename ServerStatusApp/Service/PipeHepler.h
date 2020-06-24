#ifndef PIPEHEPLER_H
#define PIPEHEPLER_H

#include "Service/StatusPipe.h"
#include "Models/ServerInfo.h"

class PipeHepler
{
private:
    StatusPipe status;

public:
    bool getStatus(ServerInfo& info);
};

#endif // PIPEHEPLER_H
