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
    virtual ~RegisterMessage() {}

    void calculateSerializedSize();
    void serialize();
};
#endif // REGISTERMESSAGE_H
