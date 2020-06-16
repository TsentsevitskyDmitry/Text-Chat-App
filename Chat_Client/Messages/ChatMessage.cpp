#include "ChatMessage.h"
#include "Messages/MessageType.h"

void ChatMessage::calculateSerializedSize()
{
    serializedSize = messageData.length();
}

void ChatMessage::_serialize(char *addr)
{
    memcpy(addr, messageData.data(), messageData.length());
}

bool ChatMessage::restore(char *data, size_t size)
{
    messageData = std::string(data, size);
    return messageData.length();
}

MessageType ChatMessage::getMessageType()
{
    return MessageType::CHAT_MESSAGE;
}

std::string ChatMessage::getData()
{
    return messageData;
}
