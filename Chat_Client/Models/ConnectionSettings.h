#ifndef CONNECTIONSETTINGS_H
#define CONNECTIONSETTINGS_H

#include <string>

class ConnectionSettings
{
private:
    std::string ip;
    std::string port;
    std::string name;

public:
    ConnectionSettings(std::string _ip, std::string _port, std::string _name) : ip(_ip), port(_port), name(_name) {}
    ConnectionSettings() {}

    const char* getIp();
    const char* getPort();
    std::string getName();
};

#endif // CONNECTIONSETTINGS_H
