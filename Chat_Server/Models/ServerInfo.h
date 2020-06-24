#ifndef SERVERINFO_H
#define SERVERINFO_H

#include <stdint.h>
#include <string>

struct DataRepresentation{
    uint32_t val1;
    uint32_t val2;
};

class ServerInfo
{
private:
    uint32_t usersCount;
    uint32_t runningPort;
    char* serializedData;
    size_t serializedSize;

public:
    ServerInfo(uint32_t _usersCount, uint32_t _runningPort) : usersCount(_usersCount), runningPort(_runningPort), serializedData(nullptr) {}

    uint32_t getUsersCount() const;
    void setUsersCount(const uint32_t &value);
    uint32_t getRunningPort() const;
    void setRunningPort(const uint32_t &value);

    void serialize();
    char* getSerializedData();
    size_t getSerializedSize();
};

#endif // SERVERINFO_H
