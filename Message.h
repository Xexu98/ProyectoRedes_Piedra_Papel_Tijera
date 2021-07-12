#pragma once
#include "Serializable.h"
#include  <string>
#include <SDL2/SDL.h>
#include "ObjectInfo.h"
class Jugador;


enum class MessageType: int8_t
{
    LOGIN   = 0,
    PLAYERINFO = 1,
    PIEDRA = 2,
    PAPEL = 3,
    TIJERAS = 4,
    UNDEFINED = 5,
    LOGOUT  = 6,
    NEWPLAYER = 7,
    LOOSE=8,
    WIN=9,
    DRAW=10
};

class Message: public Serializable{
protected:
    size_t messageSize = sizeof(MessageType);
    MessageType type;
    SDL_Rect dimensions;
    std::string nick;
    ObjectInfo objectInfo;
   

    //Metodos para la serializacion de nuestros mensajes
    void serializeTypeNick();
    void serializeObjectInfo();

    //Metodos para la construccion de los mensajes recibidos
    void constructTypeNick(char *bobj);
    void constructObjectInfo(char *bobj);

public:
    
    Message();
    Message(MessageType type_ );
    
    virtual ~Message();

    virtual void to_bin();
    virtual int from_bin(char * bobj);

    size_t getMessageSize();
    MessageType getMessageType();
    std::string getNick();
    ObjectInfo getObjectInfo()const{
        return objectInfo;
    }
    
    void setNick(std::string newNick);
    void setObjectInfo(const ObjectInfo& info){
        objectInfo= info;
    }
    void setMsgType(MessageType type);

};