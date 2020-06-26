#ifndef STATUSPIPE_H
#define STATUSPIPE_H

#include <cstddef> // std::size_t
#include "windows.h"
#define PIPE_NAME "\\\\.\\pipe\\$ChatAppServerStatus$"

class StatusPipe
{
private:
    HANDLE hNamedPipe;

public:
//    StatusPipe();

    bool create();
    bool waitClient();
    void disconnect();
    void close();
    void stop();

    bool read(char* buff, size_t buffSize, size_t* recvBytes);
    bool write(char* buff, size_t size);
};

#endif // STATUSPIPE_H
