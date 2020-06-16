#include "ServerSocket.h"

ServerSocket::~ServerSocket()
{
    disconnect();
}

bool ServerSocket::isConnected()
{
    return connected;
}

void ServerSocket::disconnect()
{
    // cleanup
    closesocket(connectSocket);
    WSACleanup();
}

bool ServerSocket::try_connect()
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

    connectSocket  = INVALID_SOCKET;
    ptr=result;

    connectSocket  = socket(ptr->ai_family, ptr->ai_socktype,
        ptr->ai_protocol);

    if (connectSocket  == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        connected = false;
        return false;
    }

    // Connect to server.
    iResult = connect( connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(connectSocket );
        connectSocket = INVALID_SOCKET;
        connected = false;
    }

    freeaddrinfo(result);

    if (connectSocket  == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        connected = false;
        return false;
    }

    connected = true;
    return true;
}

bool ServerSocket::sendRaw(char *data, size_t size)
{
        // Send an initial buffer
        int iResult = send(connectSocket, data, static_cast<int>(size), 0);
        if (iResult == SOCKET_ERROR) {
            printf("send failed: %d\n", WSAGetLastError());
            closesocket(connectSocket);
            connected = false;
            return false;
        }

        printf("Bytes Sent: %ld\n", iResult);
        return true;
}

bool ServerSocket::recvRaw(char** buff, size_t* size)
{
    static char recvbuff[DEFAULT_BUFLEN];
    int iResult = recv(connectSocket, recvbuff, DEFAULT_BUFLEN, 0);
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

bool ServerSocket::recvRawBytes(char **buff, size_t *size, size_t buffLen)
{
    // TODO: if data more then IP packet
    recvRaw(buff, size);
}
