#include "ClientProcessor.h"


ClientProcessor::~ClientProcessor()
{
    releaseClient();
}

void ClientProcessor::process()
{
    if(!registerClient()){
        cout << "user already exist" << endl;
        return;
    }
    else{
        cout << "done!!!" << endl;
    }


    while(helper.isClientConnected())
    {
        ChatMessage cm;
        if(!helper.recvChatMessage(cm)){
            return;
        }

        cout << clientName << ": " << cm.getData() << endl;
    }
}

bool ClientProcessor::registerClient()
{
    bool success = helper.recvRegistrationName(clientName);
    if(success){
        server->lockClients();
        auto clients = server->getClients();
        auto [pair, result] = clients->insert({clientName, info});
        success = result;
        server->unlockClients();
    }
    return success;
}

void ClientProcessor::releaseClient()
{
    server->lockClients();
    auto clients = server->getClients();
    clients->erase(clientName);
    server->unlockClients();
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
