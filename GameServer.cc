#include "GameServer.h"
#include "Message.h"
#include <memory>
#include <ctime>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <list>
#include "Constants.h"

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
        case MessageType::PIEDRA:
        {
        }
          case MessageType::PAPEL:
        {
        }
          case MessageType::TIJERAS:
        {
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

void GameServer::checkCollisions()
{

    std::list<std::map<std::string, ObjectInfo>::iterator> playersToErase;
    std::list<std::map<std::string, ObjectInfo>::iterator> objectsToErase;

    //colision de players con otros players
    for (auto it = players.begin(); it != players.end(); ++it)
    {
        for (auto it2 = std::next(it); it2 != players.end(); ++it2)
        {
            SDL_Rect a, b;
            ObjectInfo ap = (*it).second, bp = (*it2).second;
            a = {(int)ap.pos.getX(), (int)ap.pos.getY(), ap.tam, ap.tam};
            b = {(int)bp.pos.getX(), (int)bp.pos.getY(), bp.tam, bp.tam};

            //Si se solapan y el tamaño entre los dos es distinto
            //significa que uno muere
            if (SDL_HasIntersection(&a, &b) && bp.tam != ap.tam)
            {
                if (ap.tam > bp.tam)
                {
                    playersToErase.push_back(it2);
                }
                else
                {
                    playersToErase.push_back(it);
                }
            }
        }
    }
}

void GameServer::createObjects()
{
    
}