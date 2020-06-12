#ifndef SERVICEMESSAGE_H
#define SERVICEMESSAGE_H

#include "Messages/BaseMessage.h"
#include <stdint.h>

class ServiceMessage : public BaseMessage
{
private:
    uint8_t contentType;
    size_t contentSize;

public:
    ServiceMessage(uint8_t contentType, size_t contentSize);
    virtual ~ServiceMessage() {}

    void calculateSerializedSize();
    void serialize();
    void restore(char* data);

    uint8_t getContentType();
    size_t getContentSize();
};

#endif // SERVICEMESSAGE_H
