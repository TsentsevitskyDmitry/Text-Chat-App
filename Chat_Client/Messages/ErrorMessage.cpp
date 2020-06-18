#include "ErrorMessage.h"


void ErrorMessage::calculateSerializedSize()
{
       serializedSize = sizeof(error);
}

void ErrorMessage::_serialize(char *addr)
{
    memcpy(addr, &error, sizeof(error));
}

bool ErrorMessage::restore(char *data, size_t size)
{
    memcpy(&error, data, size);
    return true;
}

MessageType ErrorMessage::getMessageType()
{
    return MessageType::ERROR_MESSAGE;
}

ErrorType ErrorMessage::getError()
{
    return error;
}

void ErrorMessage::setError(ErrorType error)
{
    this->error = error;
}
