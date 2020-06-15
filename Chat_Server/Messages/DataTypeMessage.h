#ifndef SERVICEMESSAGE_H
#define SERVICEMESSAGE_H

#include "Messages/BaseMessage.h"
#include <stdint.h>

class DataTypeMessage : public BaseMessage
{
private:
    uint8_t contentType;
    size_t contentSize;

public:
    DataTypeMessage(uint8_t contentType, size_t contentSize);
    DataTypeMessage() : contentType(0), contentSize(0) {}
    virtual ~DataTypeMessage() {}

    void calculateSerializedSize();
    void serialize();
    void restore(char* data, size_t size);

    MessageType getMessageType();
    uint8_t getContentType();
    size_t getContentSize();
};

#endif // SERVICEMESSAGE_H
