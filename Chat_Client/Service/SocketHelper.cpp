#include "SocketHelper.h"

bool SocketHelper::isConnected()
{
    return socket.isConnected();
}

void SocketHelper::disconnect()
{
    socket.disconnect();
}

bool SocketHelper::tryConnect()
{
    return socket.try_connect();
}

bool SocketHelper::sendMessage(BaseMessage &message)
{
    message.serialize();
    return socket.sendRaw(message.getSerializedData(), message.getSerializedSize());
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

bool SocketHelper::recvChatMessage(BaseMessage &message)
{
    return recvMessage(message, MessageType::CHAT_MESSAGE);
}
