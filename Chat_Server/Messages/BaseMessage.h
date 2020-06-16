#ifndef BASEMESSAGE_H
#define BASEMESSAGE_H

#include <cstddef> // std::size_t
#include <stdint.h>
#include "Messages/MessageType.h"

struct MetaData {
    uint8_t contentType;
    size_t contentSize;
};

class BaseMessage
{
private:
    char* serializedData;
    void clear();

protected:
    std::size_t serializedSize;
    virtual void _serialize(char* addr) = 0;
    virtual void calculateSerializedSize() = 0;

public:
    BaseMessage() : serializedData(nullptr) {}
    virtual ~BaseMessage();

    virtual MessageType getMessageType() = 0;

    size_t getSerializedSize();
    char* getSerializedData();

    bool isSerialized();
    void serialize();

    virtual bool restore(char* data, size_t size) = 0;
};

#endif // BASEMESSAGE_H
