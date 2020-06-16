#include "Messages/RegisterMessage.h"
#include "Messages/MessageType.h"

void RegisterMessage::calculateSerializedSize()
{
    serializedSize = name.length();
}

void RegisterMessage::serialize()
{
    clear();
    calculateSerializedSize();
    serializedData = new char[serializedSize];
    memcpy(serializedData, name.c_str(), name.length());
}

void RegisterMessage::restore(char *data, size_t size)
{
    name = std::string(data, size);
}

MessageType RegisterMessage::getMessageType()
{
    return MessageType::REGISTRATION;
}

std::string&  RegisterMessage::getName()
{
    return name;
}
