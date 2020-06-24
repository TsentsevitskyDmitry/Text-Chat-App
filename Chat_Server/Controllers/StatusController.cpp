#include "StatusController.h"

bool StatusController::isRunning()
{
    return running;
}

void StatusController::start()
{
    running = true;
    while (running) {
        helper.waitAndSend();
    }
}

void StatusController::stop()
{
    running = false;
    helper.clean();
}
