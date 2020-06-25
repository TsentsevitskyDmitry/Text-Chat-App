#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include <string>

class ServerConfig
{
private:
    std::string port;

public:
    ServerConfig() : port("0") {}

    std::string getPort();
    void setPort(std::string& port);
};

#endif // SERVERCONFIG_H
