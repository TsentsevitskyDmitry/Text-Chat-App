#include "BaseMessage.h"

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
