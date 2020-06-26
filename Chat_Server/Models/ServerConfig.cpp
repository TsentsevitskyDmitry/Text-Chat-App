#include "ServerConfig.h"

std::string ServerConfig::getPort() {
    return port;
}

void ServerConfig::setPort(std::string& port) {
    this->port = port;
}
