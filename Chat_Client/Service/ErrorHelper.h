#ifndef ERRORHELPER_H
#define ERRORHELPER_H

#include <string>
#include <utility>
#include "Messages/MessageTypes.h"
#include "Service/SocketHelper.h"

class ErrorHelper
{
public:
    static std::pair<bool, std::string> parseRegistrationError(ErrorType error, std::string_view name);
    static std::string messageNotSent(std::string_view message);
};

#endif // ERRORHELPER_H
