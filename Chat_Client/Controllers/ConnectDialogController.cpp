#include "ConnectDialogController.h"

ConnectionSettings ConnectDialogController::settings;

void ConnectDialogController::connectButtonClicked(string ip, string port, string name)
{
    // validation here
    settings = ConnectionSettings(ip, port, name);
    chat->setup(settings);
}

ConnectionSettings& ConnectDialogController::getPrevSettings()
{
    return settings;
}
