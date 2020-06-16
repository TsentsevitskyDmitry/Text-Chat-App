#include "ChatMessage.h"
#include "Messages/MessageType.h"

void ChatMessage::calculateSerializedSize()
{
    serializedSize = messageData.length();
}

void ChatMessage::serialize()
{
    clear();
    calculateSerializedSize();
    serializedData = new char[serializedSize];
    memcpy(serializedData, messageData.data(), messageData.length());
}

void ChatMessage::restore(char *data, size_t size)
{
    messageData = std::string(data, size);

}

MessageType ChatMessage::getMessageType()
{
    return MessageType::CHAT_MESSAGE;
}

std::string ChatMessage::getData()
{
    return messageData;
}
