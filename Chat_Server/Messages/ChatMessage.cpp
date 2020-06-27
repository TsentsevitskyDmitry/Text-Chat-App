#include "ChatMessage.h"
#include "Messages/MessageTypes.h"

void ChatMessage::calculateSerializedSize()
{
    serializedSize = messageData.length() + sender.length() + 2 * sizeof(size_t);
}

void ChatMessage::_serialize(char *addr)
{
    size_t* messageDataSize = reinterpret_cast<size_t*>(addr);
    *messageDataSize = messageData.length();
    addr += sizeof (size_t);
    memcpy(addr, messageData.data(), messageData.length());
    addr += messageData.length();

    size_t* senderSize = reinterpret_cast<size_t*>(addr);
    *senderSize = sender.length();
    addr += sizeof (size_t);
    memcpy(addr, sender.data(), sender.length());
}

bool ChatMessage::restore(char *data, size_t size)
{
    size_t* messageDataSize = reinterpret_cast<size_t*>(data);
    data += sizeof (size_t);
    messageData = std::string(data, *messageDataSize);
    data += messageData.length();

    size_t* senderSize = reinterpret_cast<size_t*>(data);
    data += sizeof (size_t);
    sender = std::string(data, *senderSize);

    calculateSerializedSize();
    return serializedSize == size;
}

MessageType ChatMessage::getMessageType()
{
    return MessageType::CHAT_MESSAGE;
}

std::string ChatMessage::getData()
{
    return messageData;
}

std::string ChatMessage::getSender()
{
    return sender;
}
