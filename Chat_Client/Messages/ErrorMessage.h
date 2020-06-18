#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

#include "Messages/BaseMessage.h"
#include <string>

class ErrorMessage : public BaseMessage
{
private:
    ErrorType error;

    void _serialize(char* addr);

public:
    ErrorMessage(ErrorType _error) : error(_error) {}
    ErrorMessage() : error(ErrorType::NO_ERROR_ERROR) {}
    virtual ~ErrorMessage() {}

    void calculateSerializedSize();
    bool restore(char* data, size_t size);


    MessageType getMessageType();
    ErrorType getError();
    void setError(ErrorType error);
};

#endif // ERRORMESSAGE_H
