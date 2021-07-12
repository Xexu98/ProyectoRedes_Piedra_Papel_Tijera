#include "Game.h"
#include "Message.h"
#include "Resources.h"
#include "InputManager.h"
#include "Constants.h"

void Game::initGame()
{
    //Mandamos mensaje de login
    Message logMsg = Message(MessageType::LOGIN);

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

   
    bPapel = new Button();
    bTijeras = new Button();
    bPiedra= new Button();
    bPapel->setTexture(app->getTextureManager()->getTexture(Resources::TextureId::Papel));
    bPapel->setPosition(Vector2D(200,300));
    bPapel->setTam(0.5);
    bTijeras->setTexture(app->getTextureManager()->getTexture(Resources::TextureId::Tijeras));
    bTijeras->setPosition(Vector2D(400,300));
    bTijeras->setTam(0.5);   
    bPiedra->setTexture(app->getTextureManager()->getTexture(Resources::TextureId::Piedra));
    bPiedra->setPosition(Vector2D(0,300));
    bPiedra->setTam(0.5);
    background = app->getTextureManager()->getTexture(Resources::TextureId::Escenario);
}

Game::~Game()
{
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
        }
         case MessageType::WIN:
        {
            std::cout << "Victoria \n" ;
             waitingResult=false;
        }
         case MessageType::LOOSE:
        {
            std::cout << "Has perdido \n"; 
            waitingResult=false;
        }        
        }
    }

}

void Game::input_thread()
{

if (!waitingResult)
{
   


    //Updateamos la instancia del input
    HandleEvents::instance()->update();
    
    bool sendMessage = false;
    //Movemos al jugador localmente
    if (HandleEvents::instance()->isKeyDown(SDL_SCANCODE_1))
    {
        if (isRunning)
        {
            Message m(MessageType::PIEDRA);
            socket.send(m, socket);
            waitingResult=true;
        }
        
    }
    if (HandleEvents::instance()->isKeyDown(SDL_SCANCODE_2))
    {
      if (isRunning)
        {
           Message m(MessageType::PAPEL);
            socket.send(m, socket);
             waitingResult=true;
        }
    }
    if (HandleEvents::instance()->isKeyDown(SDL_SCANCODE_3) )
    {
       if (isRunning)
        {
            Message m(MessageType::TIJERAS);
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

    //Pintamos a nuestro jugador
    mainPlayer->getPlayerTexture()->render({(int)mainPlayer->getPlayerPos().getX(),
                                            (int)mainPlayer->getPlayerPos().getY(),
                                            mainPlayer->getPlayerTam(),
                                            mainPlayer->getPlayerTam()});


    bPapel->getButtonTexture()->render();
    bTijeras->getButtonTexture()->render();
    bPiedra->getButtonTexture()->render();

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