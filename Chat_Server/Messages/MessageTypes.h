#ifndef MESSAGETYPES_H
#define MESSAGETYPES_H

enum MessageType
{
    ERROR_MESSAGE,
    REGISTRATION_MESSAGE,
    CHAT_MESSAGE
};

enum ChatMessageType
{
    TEXT_MESSAGE
};

// NO_ERROR and SOCKET_ERROR are used as macros in windows.h
enum ErrorType
{
    NO_ERROR_ERROR,
    NAME_ALREADY_USED_ERROR,
    SOCKETS_ERROR,
    INTERNAL_ERROR
};


#endif // MESSAGETYPES_H
