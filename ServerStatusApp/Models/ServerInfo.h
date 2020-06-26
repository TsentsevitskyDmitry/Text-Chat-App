#ifndef SERVERINFO_H
#define SERVERINFO_H

#include <stdint.h>
#include <string>

class ServerInfo
{
    struct ServerInfoDataRepresentation{
        uint32_t val1;
        uint32_t val2;
    };

private:
    uint32_t usersCount;
    uint32_t runningPort;

public:
    ServerInfo(uint32_t _usersCount, uint32_t _runningPort) : usersCount(_usersCount), runningPort(_runningPort) {}
    constexpr ServerInfo() : usersCount(0), runningPort(0) {}

    uint32_t getUsersCount() const;
    void setUsersCount(const uint32_t &value);
    uint32_t getRunningPort() const;
    void setRunningPort(const uint32_t &value);

    bool restore(char* data, size_t size);
    static constexpr size_t getSerializedSize(){
        return sizeof (ServerInfoDataRepresentation);
    }
};

#endif // SERVERINFO_H
