#include "StatusPipe.h"

bool StatusPipe::waitClient()
{
    hNamedPipe = CreateNamedPipeA(
        PIPE_NAME,
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        512, 512, 1000, nullptr);
    return ConnectNamedPipe(hNamedPipe, nullptr);
}

void StatusPipe::close()
{
    DisconnectNamedPipe(hNamedPipe);
    CloseHandle(hNamedPipe);
}

bool StatusPipe::read(char *buff, size_t buffSize, size_t *recvBytes)
{
    DWORD  cbRead;
    ReadFile(hNamedPipe, buff, static_cast<DWORD>(buffSize),
      &cbRead, nullptr);
    *recvBytes = static_cast<DWORD>(cbRead);
    return cbRead;
}

bool StatusPipe::write(char *buff, size_t size)
{
    DWORD  cbWritten;
    WriteFile(hNamedPipe, buff, static_cast<DWORD>(size),
      &cbWritten, nullptr);
    return cbWritten;
}
