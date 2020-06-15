#include "DataTypeMessage.h"
#include <string>

DataTypeMessage::DataTypeMessage(uint8_t contentType, size_t contentSize)
{
    this->contentType = contentType;
    this->contentSize = contentSize;
}

void DataTypeMessage::calculateSerializedSize()
{
    struct Data {
        uint8_t contentType;
        size_t contentSize;
    };
    serializedSize = sizeof(Data);
}

void DataTypeMessage::serialize()
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


void DataTypeMessage::restore(char* data, size_t size)
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

MessageType DataTypeMessage::getMessageType()
{
    return MessageType::DATA_TYPE;
}

uint8_t DataTypeMessage::getContentType()
{
    return contentType;
}

size_t DataTypeMessage::getContentSize()
{
    return contentSize;
}
