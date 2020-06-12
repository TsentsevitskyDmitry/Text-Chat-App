#include "ServiceMessage.h"
#include <string>

ServiceMessage::ServiceMessage(uint8_t contentType, size_t contentSize)
{
    this->contentType = contentType;
    this->contentSize = contentSize;
}

void ServiceMessage::calculateSerializedSize()
{
    struct Data {
        uint8_t contentType;
        size_t contentSize;
    };
    serializedSize = sizeof(Data);
}

void ServiceMessage::serialize()
{
    clear();
    calculateSerializedSize();
    serializedData = new char[serializedSize];

    struct {
        uint8_t _contentType;
        size_t _contentSize;
    } data = {contentType, contentSize};
    memcpy(serializedData, reinterpret_cast<char*>(&data), serializedSize);
}


void ServiceMessage::restore(char* data, size_t size)
{
    calculateSerializedSize();
    struct {
        uint8_t _contentType;
        size_t _contentSize;
    } sdata = {};

    memcpy(reinterpret_cast<char*>(&sdata), data, serializedSize);
    contentType = sdata._contentType;
    contentSize = sdata._contentSize;
}

uint8_t ServiceMessage::getContentType()
{
    return contentType;
}

size_t ServiceMessage::getContentSize()
{
    return contentSize;
}
