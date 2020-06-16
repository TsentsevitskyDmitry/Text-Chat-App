#ifndef BASEMESSAGE_H
#define BASEMESSAGE_H

#include <cstddef> // std::size_t
#include "Messages/MessageType.h"

class BaseMessage
{
protected:
    std::size_t serializedSize;
    char* serializedData;
    void clear();

public:
    BaseMessage() : serializedData(nullptr) {}
    virtual ~BaseMessage();

    virtual void calculateSerializedSize() = 0;
    virtual void serialize() = 0;

    virtual MessageType getMessageType() = 0;
    size_t getSerializedSize();
    char* getSerializedData();

    virtual void restore(char* data, size_t size) = 0;
};

#endif // BASEMESSAGE_H
