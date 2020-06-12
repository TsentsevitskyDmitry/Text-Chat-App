#include "Messages/RegisterMessage.h"
#include "Messages/messagetypes.h"

RegisterMessage::RegisterMessage(std::string name)
{
    this->name = name;
}

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

std::string_view RegisterMessage::getName()
{
    return name;
}
