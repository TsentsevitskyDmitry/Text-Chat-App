#ifndef BASEMESSAGE_H
#define BASEMESSAGE_H

#include <cstddef> // std::size_t

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
    size_t getSerializedSize();
    char* getSerializedData();
};

#endif // BASEMESSAGE_H
