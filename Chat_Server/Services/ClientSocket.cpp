#include "ClientSocket.h"

bool ClientSocket::sendRaw(char *data, size_t size)
{
    return sendRawTo(data, size, clientSocket);
}

bool ClientSocket::sendRawTo(char *data, size_t size, SOCKET socket)
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

bool ClientSocket::recvRaw(char* buff, size_t* size, size_t buffLen)
{
    int iResult = recv(clientSocket, buff, static_cast<int>(buffLen), 0);
    if (iResult > 0) {
        printf("Bytes received: %d\n", iResult);
    }
    else {
        printf("recv failed: %d\n", WSAGetLastError());
        clientConnected = false;
        return false;
    }
    *size = static_cast<size_t>(iResult);
    return true;
}


ClientSocket::~ClientSocket()
{
    disconnect();
}

bool ClientSocket::isClientConnected()
{
    return clientConnected;
}

void ClientSocket::disconnect()
{
    // cleanup
    clientConnected = false;
    closesocket(clientSocket);
}
