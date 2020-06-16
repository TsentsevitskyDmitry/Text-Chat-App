#include "BaseMessage.h"
#include <string>

void BaseMessage::clear()
{
    if (serializedData != nullptr){
        delete[] serializedData;
    }
}

BaseMessage::~BaseMessage()
{
    clear();
}

size_t BaseMessage::getSerializedSize()
{
    return serializedSize;
}

char *BaseMessage::getSerializedData()
{
    return serializedData;
}

void BaseMessage::serialize()
{
    clear();
    calculateSerializedSize();
    MetaData meta = {static_cast<uint8_t>(getMessageType()), serializedSize};
    serializedSize += sizeof(meta);
    serializedData = new char[serializedSize];
    memcpy(serializedData, &meta, sizeof(meta));
    _serialize(serializedData + sizeof(meta));
}
