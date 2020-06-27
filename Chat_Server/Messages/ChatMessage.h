#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include "Messages/BaseMessage.h"
#include <string>

class ChatMessage : public BaseMessage
{
private:
    std::string messageData;
    std::string sender;
    void _serialize(char* addr);

public:
    ChatMessage(std::string_view _data, std::string_view _sender) : messageData(_data), sender(_sender) {}
    ChatMessage() : messageData("") {}
    virtual ~ChatMessage() {}

    void calculateSerializedSize();
    bool restore(char* data, size_t size);

    MessageType getMessageType();
    std::string getData();
    std::string getSender();
};

#endif // CHATMESSAGE_H
