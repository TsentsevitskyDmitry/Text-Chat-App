#include "ClientProcessor.h"


bool ClientProcessor::registerClient(ClientInfo &info)
{
    cout << "processing" << endl;
    ServiceMessage sm;
    recvServiceMessage(sm);

    if(sm.getContentType() == MessageType::REGISTRATION){
        RegisterMessage rm;
        recvMessage(rm, sm.getContentSize());

        cout << "name=" << rm.getName() << endl;
    }
    else{
        // need some feedback to the client
        return false;
    }

    return true;
}

void ClientProcessor::process()
{
    ClientInfo info;
    registerClient(info);


}

bool ClientProcessor::sendMessage(BaseMessage &message)
{
    message.serialize();
    return socket.sendRaw(message.getSerializedData(), message.getSerializedSize());
}

bool ClientProcessor::recvMessage(BaseMessage &message, size_t buffSize)
{
    char* data = nullptr;
    size_t size;
    bool result = socket.recvRawBytes(&data, &size, buffSize);
    if (result){
        message.restore(data, size);
    }
    return result;
}

bool ClientProcessor::recvServiceMessage(ServiceMessage &message)
{
    char* data = nullptr;
    size_t size;
    bool result = socket.recvRaw(&data, &size);
    if (result){
        message.restore(data, size);
    }
    return result;
}


void legacyRwEcho()
{
    //    cout << "hello from new thread" << endl;

    //    char recvbuf[DEFAULT_BUFLEN];
    //    int iSendResult, iResult;
    //    int recvbuflen = DEFAULT_BUFLEN;

    //    // Receive until the peer shuts down the connection
    //    do {

    //        iResult = recv(clientSocket, recvbuf, recvbuflen, 0);
    //        if (iResult > 0) {
    //            printf("Bytes received: %d\n", iResult);
    //            printf("%s\n", recvbuf);

    ////            // Echo the buffer back to the sender
    ////            iSendResult = send(clientSocket, recvbuf, iResult, 0);
    ////            if (iSendResult == SOCKET_ERROR) {
    ////                printf("send failed: %d\n", WSAGetLastError());
    ////                closesocket(clientSocket);
    ////                return;
    ////            }
    ////            printf("Bytes sent: %d\n", iSendResult);



    //        } else if (iResult == 0)
    //            printf("Connection closing...\n");
    //        else {
    //            printf("recv failed: %d\n", WSAGetLastError());
    //            closesocket(clientSocket);
    //            return;
    //        }

    //    } while (iResult > 0);


    //    // shutdown the connection since we're done
    //    iResult = shutdown(clientSocket, SD_SEND);
    //    if (iResult == SOCKET_ERROR) {
    //        printf("shutdown failed with error: %d\n", WSAGetLastError());
    //        closesocket(clientSocket);
    //        return;
    //    }

    //    // cleanup
    //    closesocket(clientSocket);
}
