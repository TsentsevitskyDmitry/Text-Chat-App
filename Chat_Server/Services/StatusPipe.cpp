#include "StatusPipe.h"
#include <ioapiset.h>

bool StatusPipe::create()
{
    hNamedPipe = CreateNamedPipeA(
        PIPE_NAME,
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        512, 512, 1000, nullptr);
    return hNamedPipe != INVALID_HANDLE_VALUE;
}

bool StatusPipe::waitClient()
{
    return ConnectNamedPipe(hNamedPipe, nullptr);
}

void StatusPipe::disconnect()
{
    DisconnectNamedPipe(hNamedPipe);
}

void StatusPipe::close()
{
    CloseHandle(hNamedPipe);
}

void StatusPipe::stop()
{
    // interrupt Synchronous ConnectNamedPipe()
    HANDLE hNamedPipe = CreateFileA(
        PIPE_NAME,
        GENERIC_READ | GENERIC_WRITE,
        0, nullptr, OPEN_EXISTING, 0, nullptr);
    CloseHandle(hNamedPipe);
    close();
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
