#include "SocketHelper.h"

bool SocketHelper::isClientConnected()
{
    return clientSocket.isClientConnected();
}

void SocketHelper::disconnect()
{
    clientSocket.disconnect();
}

bool SocketHelper::sendMessage(BaseMessage& message)
{
    message.serialize();
    return sendSerializedMessage(message);
}

bool SocketHelper::sendMessage(BaseMessage&& message)
{
    return sendMessage(message);
}

bool SocketHelper::sendSerializedMessage(BaseMessage& message)
{
    return clientSocket.sendRaw(message.getSerializedData(), message.getSerializedSize());
}

bool SocketHelper::sendSerializedMessage(BaseMessage&& message)
{
    return sendSerializedMessage(message);
}


bool SocketHelper::recvMeta(MetaData &meta)
{
    size_t size;
    return clientSocket.recvRaw(reinterpret_cast<char*>(&meta), sizeof (meta), &size);
}

bool SocketHelper::recvMessage(BaseMessage &message, MessageType type)
{
    size_t size;
    MetaData meta;
    if (!recvMeta(meta)){
        return false;
    }

    char* data = nullptr;
    try {
        data = new char[meta.contentSize];
    } catch (...) {
        return false;
    }

    bool success = clientSocket.recvRaw(data, meta.contentSize, &size);
    if (!success || meta.contentType != type){
        return false;
    }
    message.restore(data, size);
    delete[] data;

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
