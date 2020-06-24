#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include <string>

class ServerConfig
{
private:
    std::string port;

public:
    ServerConfig(std::string _port) : port(_port) {}

    std::string getPort();
    void setPort(std::string& port);
};

#endif // SERVERCONFIG_H
