#include "ServerSocket.h"

ServerSocket::~ServerSocket()
{
    disconnect();
}

void ServerSocket::setup(ConnectionSettings& settings)
{
    ip = settings.getIp();
    port = settings.getPort();
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

bool ServerSocket::tryConnect()
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

    struct addrinfo *result = nullptr,
                    *ptr = nullptr,
                    hints;

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(this->ip.c_str(), this->port.c_str(), &hints, &result);
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
        freeaddrinfo(result);
        connected = false;
        return false;
    }

    // Connect to server.
    iResult = connect( connectSocket, ptr->ai_addr, static_cast<int>(ptr->ai_addrlen));
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
//        printf("Bytes Sent: %ld\n", iResult);
        return true;
}

bool ServerSocket::recvRaw(char* buff, size_t buffSize, size_t* recvBytes)
{
    int iResult = recv(connectSocket, buff, static_cast<int>(buffSize), 0);
    if (iResult > 0) {
//        printf("Bytes received: %d\n", iResult);
    }
    else {
        printf("recv failed: %d\n", WSAGetLastError());
        connected = false;
        return false;
    }
    *recvBytes = static_cast<size_t>(iResult);
    return true;
}

int ServerSocket::getLastErrorCode()
{
    return  WSAGetLastError();
}
