#include "GameServer.h"
#include "Message.h"
#include <memory>
#include <ctime>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <list>
#include "Constants.h"

Message c1,c2;

GameServer::GameServer(const char *s, const char *p) : socket(s, p)
{
    //Inicializamos seed para numeros aleatorios
    srand(std::time(0));
    initTime = SDL_GetTicks();
}

void GameServer::do_messages()
{

    if (socket.bind() == -1)
    {
        std::cout << "Bindeo Incorrecto\n";
    }

    while (true)
    {
        Message cm;
        Socket *s = nullptr;

        //Esperamos recibir un mensaje de cualquier socket
        if (socket.recv(cm, s) == -1)
        {
            std::cout << "Error al recibir el mensaje\n";
        }

        //Recibir Mensajes en y en función del tipo de mensaje
        switch (cm.getMessageType())
        {
        case MessageType::LOGIN:
        {
            
            //Lo añadimos a la lista de clientes convirtiendo el socket en un unique_ptr y usando move
            clients[cm.getNick()] = std::move(std::make_unique<Socket>(*s));

            //Informacion del jugador
            ObjectInfo n;
            n.tam = INITIAL_PLAYER_SIZE;
            n.pos = Vector2D(rand() % (WINDOW_WIDTH - n.tam), rand() % (WINDOW_HEIGHT - n.tam));

            //Asignamos
            players[cm.getNick()] = n;

            //Mandarle al player que se acaba de conectar su posicion y su tam
            //Avisar al resto de jugadores que se ha conectado un nuevo jugador
            //Reenviar el mensaje a todos los clientes
            Message newPlayerConnected = Message();
            newPlayerConnected.setMsgType(MessageType::NEWPLAYER);
            newPlayerConnected.setNick(cm.getNick());
            newPlayerConnected.setObjectInfo(players[cm.getNick()]);
             std::cout << "newplayer\n";
            //Avisar a todos los jugadores conectados que ha entrado uno nuevo
            for (auto it = clients.begin(); it != clients.end(); it++)
            {
                //enviarlo a todos
                socket.send(newPlayerConnected, *((*it).second.get()));
            }

            //Avisar al que ha entrado de donde estan el resto
            for (auto it = players.begin(); it != players.end(); ++it)
            {
                if ((*it).first != cm.getNick())
                {
                    newPlayerConnected.setNick((*it).first);
                    newPlayerConnected.setObjectInfo((*it).second);
                    socket.send(newPlayerConnected, *s);
                }
            }

            break;
        }

        case MessageType::LOGOUT:
        {
            auto it = clients.begin();

            while (it != clients.end() && (*((*it).second.get()) != *s))
                ++it;

            if (it == clients.end())
                std::cout << "El jugador ya se había desconectado previamente\n";
            else
            {
                std::cout << "Jugador desconectado: " << cm.getNick() << "\n";
                clients.erase((*it).first);               //Lo sacamos del vector
                Socket *delSock = (*it).second.release(); //Eliminamos la pertenencia del socket de dicho unique_ptr
                delete delSock;                           //Borramos el socket
            }
            break;
        }

        case MessageType::PLAYERINFO:
        {
            //Actualizamos la posición en la que se encuentra dicho jugador en la memoria del servidor
            players[cm.getNick()] = cm.getObjectInfo();

            //Avisar a todos los jugadores conectados que alguien se ha movido
            for (auto it = clients.begin(); it != clients.end(); it++)
            {
                if (*((*it).second.get()) != *s) //Excepto a la persona que ha enviado el mensaje
                {
                    socket.send(cm, (*((*it).second.get())));
                }
            }
            std::cout << "entro\n";
            break;
        }
         case MessageType::PIEDRA:
        {
             if (!elegidoC1)
          {
                nickC1=cm.getNick();
                elegidoC1=true;
                c1.setMsgType(cm.getMessageType());
          }
          else
          {
              nickC2=cm.getNick();
                elegidoC2=true;
                c2.setMsgType(cm.getMessageType());
          }
            std::cout<<"Piedra \n"; 
            break;
        }

         case MessageType::PAPEL:
        {
             if (!elegidoC1)
          {
                nickC1=cm.getNick();
                elegidoC1=true;
                c1.setMsgType(cm.getMessageType());
          }
          else
          {
              nickC2=cm.getNick();
                elegidoC2=true;
                c2.setMsgType(cm.getMessageType());
          }
            std::cout<<"PAPEL \n"; 
            break;
        }

         case MessageType::TIJERAS:
        {
             if (!elegidoC1)
          {
                nickC1=cm.getNick();
                elegidoC1=true;
                c1.setMsgType(cm.getMessageType());
          }
          else
          {
                nickC2=cm.getNick();
                elegidoC2=true;
                c2.setMsgType(cm.getMessageType());
          }
            std::cout<<"TIJERAS \n"; 
            break;
        }
        default:
            break;
        }

        //En el metodo recieve si recibimos como parametro un puntero hacemos un new con el socket creado
        //A excecpción del que recibamos un mensaje de login, siempre querremos borrar ese objeto
        //puesto que ya lo almacenamos en el diccionario clients y no borrarlo dejaria basura
        if(cm.getMessageType() != MessageType::LOGIN){
            delete s;
        }

    }
}
void GameServer::compruebaResultados()
{
 if (elegidoC1 && elegidoC2)
    {
        Message aux;
        if (c1.getMessageType() == c2.getMessageType())
        {
            aux.setMsgType(MessageType::DRAW);
            socket.send(aux, *clients[nickC1].get());
            socket.send(aux, *clients[nickC2].get());
        }
        else if (c1.getMessageType() == MessageType::PAPEL  && c2.getMessageType()==  MessageType::PIEDRA)
        {
            aux.setMsgType(MessageType::WIN);
            socket.send(aux, *clients[nickC1].get());
            aux.setMsgType(MessageType::LOOSE);
            socket.send(aux, *clients[nickC2].get());
        }
         else if (c1.getMessageType() == MessageType::TIJERAS && c2.getMessageType()== MessageType::PAPEL )
        {
            aux.setMsgType(MessageType::WIN);
            socket.send(aux, *clients[nickC1].get());
            aux.setMsgType(MessageType::LOOSE);
            socket.send(aux, *clients[nickC2].get());
        }
         else if (c1.getMessageType() == MessageType::PIEDRA  && c2.getMessageType()==  MessageType::TIJERAS)
        {
            aux.setMsgType(MessageType::WIN);
            socket.send(aux, *clients[nickC1].get());
            aux.setMsgType(MessageType::LOOSE);
            socket.send(aux, *clients[nickC2].get());
        }


        else if (c2.getMessageType() == MessageType::PAPEL  && c1.getMessageType()==  MessageType::PIEDRA)
        {
            aux.setMsgType(MessageType::WIN);
            socket.send(aux, *clients[nickC2].get());
            aux.setMsgType(MessageType::LOOSE);
            socket.send(aux, *clients[nickC1].get());
        }
         else if (c2.getMessageType() == MessageType::TIJERAS && c1.getMessageType()== MessageType::PAPEL )
        {
            aux.setMsgType(MessageType::WIN);
            socket.send(aux, *clients[nickC2].get());
            aux.setMsgType(MessageType::LOOSE);
            socket.send(aux, *clients[nickC1].get());
        }
         else if (c2.getMessageType() == MessageType::PIEDRA  && c1.getMessageType()==  MessageType::TIJERAS)
        {
            aux.setMsgType(MessageType::WIN);
            socket.send(aux, *clients[nickC2].get());
            aux.setMsgType(MessageType::LOOSE);
            socket.send(aux, *clients[nickC1].get());
        }
        
        elegidoC2=false;
        elegidoC1=false;
    }
}
