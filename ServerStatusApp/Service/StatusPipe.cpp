#include "StatusPipe.h"

bool StatusPipe::open()
{
    hNamedPipe = CreateFileA(
        PIPE_NAME,
        GENERIC_READ | GENERIC_WRITE,
        0, nullptr, OPEN_EXISTING, 0, nullptr);
    return hNamedPipe != INVALID_HANDLE_VALUE ? true : false;
}

void StatusPipe::close()
{
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

int StatusPipe::getLastErrorCode()
{
    return  GetLastError();
}

