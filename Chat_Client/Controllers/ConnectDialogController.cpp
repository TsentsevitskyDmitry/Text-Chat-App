#include "ConnectDialogController.h"

ConnectionSettings ConnectDialogController::settings;

bool ConnectDialogController::connectButtonClicked(string ip, string port, string name)
{
    if(!ip.length() || !port.length() || !name.length())
        return false;
    settings = ConnectionSettings(ip, port, name);
    chat->setup(settings);
    return true;
}

ConnectionSettings& ConnectDialogController::getPrevSettings()
{
    return settings;
}
