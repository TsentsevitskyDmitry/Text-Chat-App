#include "StatusController.h"

bool StatusController::isRunning()
{
    return running;
}

void StatusController::start()
{
    running = true;
    helper.create();
    while (running) {
        helper.waitAndSend();
    }
    helper.close();
}

void StatusController::stop()
{
    running = false;
    helper.stop();
}
