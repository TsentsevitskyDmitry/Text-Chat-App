#include "ErrorHelper.h"

std::pair<bool, string> ErrorHelper::parseRegistrationError(ErrorType error, std::string_view name)
{
    switch (error) {
    case ErrorType::NO_ERROR_ERROR:
        return {true, "> Connection success"};
    case ErrorType::SOCKETS_ERROR:
        return {false, "> Can't connect to the server, winsock error: " + to_string(SocketHelper::getSocketErrorCode())};
    case ErrorType::NAME_ALREADY_USED_ERROR:
        return {false, "> Can't connect to the server, name '" + std::string(name) + "' already in use."};
    default:
        return {false, "> Internal error."};
    }
}

string ErrorHelper::messageNotSent(string_view message)
{
    return "> " + string(message) + " [message not sent, please reconnect]";
}
