#include "Game.h"
#include "Message.h"
#include "Resources.h"
#include "InputManager.h"
#include "Constants.h"

void Game::initGame()
{
    //Mandamos mensaje de login
    Message logMsg = Message(MessageType::LOGIN, piedra);

    if (socket.send(logMsg, socket) == -1)
    {
        std::cout << "Error al enviar el mensaje de login\n";
    }
}

Game::Game(const char *s, const char *p, const char *n) : socket(s, p)
{
    app = SDLApp::GetInstance();

    //Creacion de las texturas
    for (auto &image : Resources::imageRoutes)
    {
        app->getTextureManager()->loadFromImg(image.textureId, app->getRenderer(), image.filename);
    }

   // mainPlayer = new Jugador(n);
   // mainPlayer->setTexture(app->getTextureManager()->getTexture(Resources::TextureId::Jugador1));
    
    piedra= new Button(n);
    piedra->setTexture(app->getTextureManager()->getTexture(Resources::TextureId::Piedra));
    piedra->setPosition(Vector2D(0,150));
    piedra->setTam(200);

      papel= new Button(n);
    papel->setTexture(app->getTextureManager()->getTexture(Resources::TextureId::Papel));
    papel->setPosition(Vector2D(200,150));
    papel->setTam(200);

      tijeras= new Button(n);
    tijeras->setTexture(app->getTextureManager()->getTexture(Resources::TextureId::Tijeras));
    tijeras->setPosition(Vector2D(400,150));
    tijeras->setTam(200);

    background = app->getTextureManager()->getTexture(Resources::TextureId::Escenario);
}

Game::~Game()
{
    //Destruir al jugador
    //delete mainPlayer;
    delete piedra;
    delete papel;
    delete tijeras;
    //Destruir tb la ventana de SDL
    delete app;
}

void Game::net_thread()
{
    while (isRunning)
    {
        //Recibir Mensajes de red
        Message em;

        socket.recv(em);

        //Mostrar en pantalla el mensaje de la forma "nick: mensaje"
        std::cout << "Recibido mensaje de: " << em.getNick() << " de tipo " << (int)em.getMessageType() << "\n";

        switch (em.getMessageType())
        {
        case MessageType::NEWPLAYER:
        {
            ObjectInfo p = em.getObjectInfo();
            if (em.getNick() != piedra->getNick())
                jugadores[em.getNick()] = p;
            else
            {
                //mainPlayer->setPosition(p.pos);
                //mainPlayer->setTam(p.tam);
            }

            break;
        }
        case MessageType::PLAYERINFO:
        {
            ObjectInfo p = em.getObjectInfo();
            jugadores[em.getNick()] = p;
            break;
        }
        case MessageType::DRAW:
        {
            std::cout << "Empate \n";
             waitingResult=false;
             break;
        }
         case MessageType::WIN:
        {
            std::cout << "Victoria \n" ;
             waitingResult=false;
             break;
        }
         case MessageType::LOOSE:
        {
            std::cout << "Has perdido \n"; 
            waitingResult=false;
            break;
        }     
        }
    }

}

void Game::input_thread()
{

    //Updateamos la instancia del input
    if (!waitingResult)
    {      
    
    HandleEvents::instance()->update();
    bool sendMessage = false;
    if (HandleEvents::instance()->isKeyDown(SDL_SCANCODE_1))
    {
        if ( isRunning)
        {
            Message m(MessageType::PIEDRA, piedra);
            socket.send(m, socket);
            waitingResult=true;
        }
    }
    if (HandleEvents::instance()->isKeyDown(SDL_SCANCODE_2))
    {
        if ( isRunning)
        {
            Message m(MessageType::PAPEL, piedra);
            socket.send(m, socket);
            waitingResult=true;
        }
    }
    if (HandleEvents::instance()->isKeyDown(SDL_SCANCODE_3))
    {
        if ( isRunning)
        {
            Message m(MessageType::TIJERAS, piedra);
            socket.send(m, socket);
            waitingResult=true;
        }
    }
    }

}

void Game::render() const
{

    //Limpiamos el renderer
    SDL_RenderClear(app->getRenderer());

    //Pintamos el fonfo
    background->render({0, 0, app->winWidth_, app->winHeight_}, SDL_FLIP_NONE);
    
    //Pintamos a los objetos

    piedra->getButtonTexture()->render({(int)piedra->getButtonPos().getX(),
                                            (int)piedra->getButtonPos().getY(),
                                            piedra->getButtonTam(),
                                            piedra->getButtonTam()});

    papel->getButtonTexture()->render({(int)papel->getButtonPos().getX(),
                                            (int)papel->getButtonPos().getY(),
                                            papel->getButtonTam(),
                                            papel->getButtonTam()});

     tijeras->getButtonTexture()->render({(int)tijeras->getButtonPos().getX(),
                                            (int)tijeras->getButtonPos().getY(),
                                            tijeras->getButtonTam(),
                                            tijeras->getButtonTam()});
   


    //Volcamos sobre la ventana
    SDL_RenderPresent(app->getRenderer());
}

void Game::run()
{
    while (isRunning)
    {
        input_thread();
        render();
    }
}