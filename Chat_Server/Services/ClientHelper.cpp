#include "ClientHelper.h"

bool ClientHelper::isClientConnected()
{
    return socket.isClientConnected();
}

bool ClientHelper::sendMessage(BaseMessage &message, ClientInfo client)
{

}

//bool ClientHelper::sendMessage(BaseMessage &message)
//{


//    message.serialize();
//    return socket.sendRaw(message.getSerializedData(), message.getSerializedSize());
//}

bool ClientHelper::recvMessage(BaseMessage &message, size_t buffSize)
{
    char* data = nullptr;
    size_t size;
    bool result = socket.recvRaw(&data, &size);
    if (result){
        message.restore(data, size);
    }
    return result;
}

bool ClientHelper::recvTypedMessage(BaseMessage &message, MessageType type)
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

bool ClientHelper::recvDataTypeMessage(DataTypeMessage &message)
{
    return recvTypedMessage(message, MessageType::DATA_TYPE);
}

bool ClientHelper::recvRegistrationMessage(BaseMessage &message)
{
    return recvTypedMessage(message, MessageType::REGISTRATION);
}

bool ClientHelper::recvChatMessage(BaseMessage &message)
{
    return recvTypedMessage(message, MessageType::CHAT_MESSAGE);
}

bool ClientHelper::recvRegistrationName(std::string& name)
{
    RegisterMessage rm;
    if(!recvRegistrationMessage(rm)){
        return false;
    }
    name = rm.getName();
    return true;
}
