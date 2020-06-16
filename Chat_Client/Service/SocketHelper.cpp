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
    message.calculateSerializedSize();
    DataTypeMessage dtm(message.getMessageType(), message.getSerializedSize());
    dtm.serialize();
    if(!socket.sendRaw(dtm.getSerializedData(), dtm.getSerializedSize())){
        return false;
    }
    message.serialize();
    return socket.sendRaw(message.getSerializedData(), message.getSerializedSize());
}

bool SocketHelper::recvMessage(BaseMessage &message, size_t buffSize)
{
    char* data = nullptr;
    size_t size;
    bool result = socket.recvRaw(&data, &size);
    if (result){
        message.restore(data, size);
    }
    return result;
}

bool SocketHelper::recvTypedMessage(BaseMessage &message, MessageType type)
{
    DataTypeMessage dtm;
    if(!recvMessage(dtm, 0)){
        return false;
    }

    if(!recvMessage(message, 0) || dtm.getContentType() != type){
        return false;
    }

    return true;
}

bool SocketHelper::recvDataTypeMessage(DataTypeMessage &message)
{
    return recvTypedMessage(message, MessageType::DATA_TYPE);
}

bool SocketHelper::recvChatMessage(BaseMessage &message)
{
    return recvTypedMessage(message, MessageType::CHAT_MESSAGE);
}
