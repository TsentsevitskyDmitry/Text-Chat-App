#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include "Messages/BaseMessage.h"
#include <string>

class ChatMessage : public BaseMessage
{
private:
    std::string messageData;

public:
    ChatMessage(std::string _data) : messageData(_data) {}
    ChatMessage() : messageData("") {}
    virtual ~ChatMessage() {}

    void calculateSerializedSize();
    void serialize();
    void restore(char* data, size_t size);

    MessageType getMessageType();
    std::string getData();
};

#endif // CHATMESSAGE_H
