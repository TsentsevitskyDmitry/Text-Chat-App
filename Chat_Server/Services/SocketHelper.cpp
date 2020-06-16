#include "SocketHelper.h"

bool SocketHelper::isClientConnected()
{
    return socket.isClientConnected();
}

bool SocketHelper::sendMessage(BaseMessage &message, ClientInfo client)
{
    message.calculateSerializedSize();
    DataTypeMessage dtm(message.getMessageType(), message.getSerializedSize());
    dtm.serialize();
    if(!socket.sendRawTo(dtm.getSerializedData(), dtm.getSerializedSize(), client.getSocket())){
        return false;
    }
    message.serialize();
    return socket.sendRawTo(message.getSerializedData(), message.getSerializedSize(), client.getSocket());
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

bool SocketHelper::recvRegistrationMessage(BaseMessage &message)
{
    return recvTypedMessage(message, MessageType::REGISTRATION);
}

bool SocketHelper::recvChatMessage(BaseMessage &message)
{
    return recvTypedMessage(message, MessageType::CHAT_MESSAGE);
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
