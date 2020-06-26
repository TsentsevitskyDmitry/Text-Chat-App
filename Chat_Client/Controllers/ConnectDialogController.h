#ifndef CONNECTDIALOGCONTROLLER_H
#define CONNECTDIALOGCONTROLLER_H

#include "Models/ConnectionSettings.h"
#include "Service/ChatClient.h"

class ConnectDialogController
{
private:
    ChatClient* chat;
    static ConnectionSettings settings;

public:
    ConnectDialogController(ChatClient* _chat) : chat(_chat) {}

    bool connectButtonClicked(std::string ip, std::string port, std::string name);
    ConnectionSettings& getPrevSettings();
};

#endif // CONNECTDIALOGCONTROLLER_H
