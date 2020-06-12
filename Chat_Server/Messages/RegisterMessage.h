#ifndef REGISTERMESSAGE_H
#define REGISTERMESSAGE_H

#include "Messages/BaseMessage.h"
#include <string>

class RegisterMessage : public BaseMessage
{
private:
    std::string name;

public:
    RegisterMessage(std::string name);
    RegisterMessage() : name("") {}
    virtual ~RegisterMessage() {}

    void calculateSerializedSize();
    void serialize();
    void restore(char* data, size_t size);

    std::string_view getName();
};
#endif // REGISTERMESSAGE_H
