#include "SocketHelper.h"

bool SocketHelper::isClientConnected()
{
    return socket.isClientConnected();
}

void SocketHelper::disconnect()
{
    socket.disconnect();
}

bool SocketHelper::sendMessage(BaseMessage& message, ClientInfo dest)
{
    message.serialize();
    return socket.sendRawTo(message.getSerializedData(), message.getSerializedSize(), dest.getSocket());
}

bool SocketHelper::recvMeta(MetaData &meta)
{
    size_t size;
    return socket.recvRaw(reinterpret_cast<char*>(&meta), &size, sizeof (meta));
}

bool SocketHelper::recvMessage(BaseMessage &message, MessageType type)
{
    size_t size;
    MetaData meta;
    if (!recvMeta(meta)){
        return false;
    }
    char* data = new char[meta.contentSize];
    bool success = socket.recvRaw(data, &size, meta.contentSize);
    if (!success || meta.contentType != type){
        return false;
    }
    message.restore(data, size);
    return true;
}

bool SocketHelper::recvRegistrationName(std::string& name)
{
    RegisterMessage rm;
    if(!recvRegistrationMessage(rm)){
        return false;
    }
    name = rm.getName();
    return true;
}

bool SocketHelper::recvRegistrationMessage(BaseMessage &message)
{
    return recvMessage(message, MessageType::REGISTRATION_MESSAGE);
}

bool SocketHelper::recvChatMessage(BaseMessage &message)
{
    return recvMessage(message, MessageType::CHAT_MESSAGE);
}
