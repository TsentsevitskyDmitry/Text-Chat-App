#include "ChatClient.h"

bool ChatClient::send(BaseMessage &message)
{
    message.serialize();
    return socket.sendRaw(message.getSerializedData(), message.getSerializedSize());
}

bool ChatClient::tryConnect()
{
    return socket.try_connect();
}

bool ChatClient::tryRegister(std::string name)
{
    RegisterMessage rm(name);
    rm.calculateSerializedSize();

    ServiceMessage sm(MessageType::REGISTRATION, rm.getSerializedSize());
    send(sm);
    send(rm);

    return true;
}
