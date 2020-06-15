#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include "Messages/BaseMessage.h"
#include <string>

class ChatMessage : public BaseMessage
{
private:
    std::string_view messageData;

public:
    ChatMessage(std::string_view _data) : messageData(_data) {}
    ChatMessage() : messageData("") {}
    virtual ~ChatMessage() {}

    void calculateSerializedSize();
    void serialize();
    void restore(char* data, size_t size);

    MessageType getMessageType();
    std::string_view getData();
};

#endif // CHATMESSAGE_H
