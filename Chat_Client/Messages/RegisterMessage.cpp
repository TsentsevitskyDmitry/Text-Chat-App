#include "Messages/RegisterMessage.h"
#include "Messages/MessageType.h"

void RegisterMessage::calculateSerializedSize()
{
    serializedSize = name.length();
}

void RegisterMessage::_serialize(char *addr)
{
    memcpy(addr, name.c_str(), name.length());
}

bool RegisterMessage::restore(char *data, size_t size)
{
    name = std::string(data, size);
    return true;
}

MessageType RegisterMessage::getMessageType()
{
    return MessageType::REGISTRATION;
}

std::string_view RegisterMessage::getName()
{
    return name;
}
