#include "ClientMessage.h"
#include <memory.h>
#include "Jugador.h"
#include <iostream>

ClientMessage::ClientMessage() : type(MessageType::UNDEFINED)
{
}
ClientMessage::ClientMessage(MessageType type_, Jugador *player_) : type(type_)
{
    nick = player_->getNick();
    objectInfo = ObjectInfo();
    objectInfo.tam = player_->getPlayerTam();
    objectInfo.pos = player_->getPlayerPos();
}

ClientMessage::~ClientMessage()
{
}

size_t ClientMessage::getMessageSize()
{
    return messageSize;
}

MessageType ClientMessage::getMessageType()
{
    return type;
}

void ClientMessage::to_bin()
{
    switch (type)
    {
    case MessageType::LOGIN:
    {
        serializeTypeNick();
        break;
    }

    case MessageType::LOGOUT:
    {
        serializeTypeNick();
        break;
    }

    case MessageType::PLAYERINFO:
    {
        serializeObjectInfo();
        break;
    }
      case MessageType::NEWPICKUP:
    {
        serializeObjectInfo();
        break;
    }

    case MessageType::NEWPLAYER:
    {
        serializeObjectInfo();
        break;
    }

    case MessageType::PLAYERDEAD:
    {
        serializeTypeNick();
        break;
    }

    case MessageType::PICKUPDESTROY:
    {
        serializeTypeNick();
        break;
    }

       case MessageType::PICKUPEAT:
    {
        serializeObjectInfo();
        break;
    }
    
    }
}

int ClientMessage::from_bin(char *bobj)
{

    //reservamos memoria para coger el tipo de mensaje
    messageSize = sizeof(MessageType);
    alloc_data(messageSize);
    //coger el tipo de mensaje
    memcpy(static_cast<void *>(_data), bobj, messageSize);

    //Reconstruir la clase usando el buffer _data
    char *temp = _data;

    //Copiamos tipo
    memcpy(&type, temp, sizeof(MessageType));

    switch (type)
    {
    case MessageType::LOGIN:
    {
        std::cout << "LOGIN\n";
        constructTypeNick(bobj);
        break;
    }

    case MessageType::LOGOUT:
    {
        std::cout << "LOGOUT\n";
        constructTypeNick(bobj);
        break;
    }

    case MessageType::PLAYERINFO:
    {
        constructObjectInfo(bobj);
        break;
    }

    case MessageType::NEWPLAYER:
    {
        std::cout << "NEWPLAYER\n";
        constructObjectInfo(bobj);
        break;
    }
    case MessageType::PLAYERDEAD:
    {
        std::cout << "PLAYERDEAD\n";
        constructTypeNick(bobj);
        break;
    }
       case MessageType::PICKUPDESTROY:
    {
        std::cout << "PICKUPDESTROY\n";
        constructTypeNick(bobj);
        break;
    }

     case MessageType::NEWPICKUP:
    {
        std::cout << "NEWPICKUP\n";
        constructObjectInfo(bobj);
        break;
    }
       case MessageType::PICKUPEAT:
    {
        std::cout << "PICKUPEAT\n";
        constructObjectInfo(bobj);
        break;
    }

    default:
        std::cout << "Ni LOG ni LOGOUT\n";
        break;
    }

    return 0;
}

std::string ClientMessage::getNick()
{
    return nick;
}

void ClientMessage::setNick(std::string newNick)
{
    nick = newNick;
}

void ClientMessage::setMsgType(MessageType type_)
{
    type = type_;
}

void ClientMessage::serializeTypeNick()
{
    //calculamos el tamaño del mensaje

    messageSize = sizeof(MessageType) + sizeof(char) * 12;
    //reservamos la memoria
    alloc_data(messageSize);
    memset(_data, 0, messageSize);

    //Serializar los campos type
    char *temp = _data;

    //Copiamos tipo de mensaje a partir de la direccion que marca temp
    //almacenamos primero el tipo de mensaje
    memcpy(temp, &type, sizeof(MessageType));

    temp += sizeof(MessageType);

    //Copiamos el nombre a partir de la direccion que marca temp
    //despues almacenamos el resto de la informacion
    memcpy(temp, nick.c_str(), sizeof(char) * 12);
}

void ClientMessage::serializeObjectInfo()
{
    messageSize = sizeof(MessageType) + sizeof(char) * 12 + sizeof(ObjectInfo);

    //reservamos la memoria
    alloc_data(messageSize);

    memset(_data, 0, messageSize);

    //Serializar los campos type
    char *temp = _data;

    //Copiamos tipo de mensaje a partir de la direccion que marca temp
    //almacenamos primero el tipo de mensaje
    memcpy(temp, &type, sizeof(MessageType));

    temp += sizeof(MessageType);

    //Copiamos el nombre a partir de la direccion que marca temp
    //despues almacenamos el resto de la informacion
    memcpy(temp, nick.c_str(), sizeof(char) * 12);

    temp += sizeof(char) * 12;

    memcpy(temp, &objectInfo, sizeof(ObjectInfo));
}

void ClientMessage::constructTypeNick(char *bobj)
{
    messageSize = sizeof(MessageType) + sizeof(char) * 12;
    //reservamos la memoria
    alloc_data(messageSize);
    memcpy(static_cast<void *>(_data), bobj, messageSize);
    //Reconstruir la clase usando el buffer _data
    char *temp = _data;
    temp += sizeof(MessageType);
    //Se puede hacer porque es un string (\0)
    nick = temp;
}

void ClientMessage::constructObjectInfo(char *bobj)
{
    messageSize = sizeof(MessageType) + sizeof(char) * 12 + sizeof(ObjectInfo);
    //reservamos la memoria
    alloc_data(messageSize);
    memcpy(static_cast<void *>(_data), bobj, messageSize);
    //Reconstruir la clase usando el buffer _data
    char *temp = _data;
    temp += sizeof(MessageType);
    //Se puede hacer porque es un string (\0)
    nick = temp;

    temp += sizeof(char) * 12;
    memcpy(&objectInfo, temp, sizeof(ObjectInfo));
}