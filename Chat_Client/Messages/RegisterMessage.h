#ifndef REGISTERMESSAGE_H
#define REGISTERMESSAGE_H

#include "Messages/BaseMessage.h"
#include <string>

class RegisterMessage : public BaseMessage
{
private:
    std::string name;

public:
    RegisterMessage(std::string_view _name) : name(_name) {}
    RegisterMessage() : name("") {}
    virtual ~RegisterMessage() {}

    void calculateSerializedSize();
    void serialize();
    void restore(char* data, size_t size);

    MessageType getMessageType();
    std::string_view getName();
};
#endif // REGISTERMESSAGE_H
