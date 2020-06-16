#include "ClientSocket.h"

ClientSocket::~ClientSocket()
{
    disconnect();
}

bool ClientSocket::isConnected()
{
    return connected;
}

void ClientSocket::disconnect()
{
    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();
}

bool ClientSocket::try_connect()
{
    disconnect();

    int iResult;
    WSADATA wsaData;

    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        connected = false;
        return false;
    }

    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        connected = false;
        return false;
    }

    ConnectSocket  = INVALID_SOCKET;
    ptr=result;

    ConnectSocket  = socket(ptr->ai_family, ptr->ai_socktype,
        ptr->ai_protocol);

    if (ConnectSocket  == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        connected = false;
        return false;
    }

    // Connect to server.
    iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(ConnectSocket );
        ConnectSocket = INVALID_SOCKET;
        connected = false;
    }

    freeaddrinfo(result);

    if (ConnectSocket  == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        connected = false;
        return false;
    }

    connected = true;
    return true;
}

bool ClientSocket::sendRaw(char *data, size_t size)
{
        // Send an initial buffer
        int iResult = send(ConnectSocket, data, static_cast<int>(size), 0);
        if (iResult == SOCKET_ERROR) {
            printf("send failed: %d\n", WSAGetLastError());
            closesocket(ConnectSocket);
            connected = false;
            return false;
        }

        printf("Bytes Sent: %ld\n", iResult);
        return true;
}

bool ClientSocket::recvRaw(char** buff, size_t* size)
{
    static char recvbuff[DEFAULT_BUFLEN];
    int iResult = recv(ConnectSocket, recvbuff, DEFAULT_BUFLEN, 0);
    if (iResult > 0) {
        printf("Bytes received: %d\n", iResult);
    }
    else {
        printf("recv failed: %d\n", WSAGetLastError());
        connected = false;
        return false;
    }
    *buff = recvbuff;
    *size = static_cast<size_t>(iResult);
    return true;
}

bool ClientSocket::recvRawBytes(char **buff, size_t *size, size_t buffLen)
{
    // TODO: if data more then IP packet
    recvRaw(buff, size);
}
