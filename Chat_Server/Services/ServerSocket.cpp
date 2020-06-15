#include "ServerSocket.h"

bool ServerSocket::sendRaw(char *data, size_t size)
{
        // Send an initial buffer
        int iResult = send(socket, data, static_cast<int>(size), 0);
        if (iResult == SOCKET_ERROR) {
            printf("send failed: %d\n", WSAGetLastError());
            closesocket(socket);
            clientConnected = false;
            return false;
        }

        printf("Bytes Sent: %ld\n", iResult);
        return true;
}

bool ServerSocket::recvRaw(char** buff, size_t* size)
{
    static char recvbuff[DEFAULT_BUFLEN];
    int iResult = recv(socket, recvbuff, DEFAULT_BUFLEN, 0);
    if (iResult > 0) {
        printf("Bytes received: %d\n", iResult);
    }
    else {
        printf("recv failed: %d\n", WSAGetLastError());
        clientConnected = false;
        return false;
    }
    *buff = recvbuff;
    *size = static_cast<size_t>(iResult);
    return true;
}

bool ServerSocket::recvRawBytes(char **buff, size_t *size, size_t buffLen)
{
    // TODO: if data more then IP packet
    recvRaw(buff, size);
}

ServerSocket::~ServerSocket()
{
    // cleanup
    closesocket(socket);
}

bool ServerSocket::isClientConnected()
{
    return clientConnected;
}
