#include "ChatClient.h"

bool ChatClient::send(BaseMessage &message)
{
    message.calculateSerializedSize();
    DataTypeMessage dtm(message.getMessageType(), message.getSerializedSize());
    dtm.serialize();
    if(!socket.sendRaw(dtm.getSerializedData(), message.getSerializedSize())){
        return false;
    }
    message.serialize();
    return socket.sendRaw(message.getSerializedData(), message.getSerializedSize());
}

bool ChatClient::tryConnect()
{
    return socket.try_connect();
}

bool ChatClient::tryRegister(std::string_view name)
{
    if(name.length() < 1){
        return false;
    }
    clientName = name;
    RegisterMessage rm(name);
    return send(rm);
}

bool ChatClient::sendTextMessage(std::string_view text)
{
    ChatMessage cm(text);
    return send(cm);
}
