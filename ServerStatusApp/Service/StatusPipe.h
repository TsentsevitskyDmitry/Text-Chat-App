#ifndef STATUSPIPE_H
#define STATUSPIPE_H

#include <cstddef> // std::size_t
#include <windows.h>
#define PIPE_NAME "\\\\.\\pipe\\$ChatAppServerStatus$"

class StatusPipe
{
private:
    HANDLE hNamedPipe;

public:
    bool open();
    void close();

    bool read(char* buff, size_t buffSize, size_t* recvBytes);
    bool write(char* buff, size_t size);
    bool call(char* wrBuff, size_t wrSize, char* rdBuff, size_t rdSize, size_t* recvBytes);
};

#endif // STATUSPIPE_H
