#include "Game.h"
#include "Message.h"
#include "Resources.h"
#include "InputManager.h"
#include "Constants.h"

void Game::initGame()
{
    //Mandamos mensaje de login
    Message logMsg = Message(MessageType::LOGIN, mainPlayer);

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

    mainPlayer = new Jugador(n);
    mainPlayer->setTexture(app->getTextureManager()->getTexture(Resources::TextureId::Jugador1));
    bPapel = new Button();
    bTijeras = new Button();
    bPiedra= new Button();
    bPapel->setTexture(app->getTextureManager()->getTexture(Resources::TextureId::Papel));
    bPapel->setPosition();
    bPapel->setTam();
    bTijeras->setTexture(app->getTextureManager()->getTexture(Resources::TextureId::Tijeras));
    bPapel->setPosition();
    bPapel->setTam();   
    bPiedra->setTexture(app->getTextureManager()->getTexture(Resources::TextureId::Piedra));
    bPapel->setPosition();
    bPapel->setTam();
    background = app->getTextureManager()->getTexture(Resources::TextureId::Escenario);
}

Game::~Game()
{
    //Destruir al jugador
    delete mainPlayer;

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
            if (em.getNick() != mainPlayer->getNick())
                jugadores[em.getNick()] = p;
            else
            {
                mainPlayer->setPosition(p.pos);
                mainPlayer->setTam(p.tam);
            }

            break;
        }
        case MessageType::PLAYERINFO:
        {
            ObjectInfo p = em.getObjectInfo();
            jugadores[em.getNick()] = p;
            break;
        }

        }
    }

}

void Game::input_thread()
{

    //Updateamos la instancia del input
    HandleEvents::instance()->update();

    Vector2D playerPos = mainPlayer->getPlayerPos();
    bool sendMessage = false;
    //Movemos al jugador localmente
    if (HandleEvents::instance()->isKeyDown(SDL_SCANCODE_1))
    {
        if (isRunning)
        {
            Message m(MessageType::PIEDRA, mainPlayer);
            socket.send(m, socket);
        }
        
    }
    if (HandleEvents::instance()->isKeyDown(SDL_SCANCODE_2))
    {
      if (isRunning)
        {
           Message m(MessageType::PAPEL, mainPlayer);
            socket.send(m, socket);
        }
    }
    if (HandleEvents::instance()->isKeyDown(SDL_SCANCODE_3) )
    {
       if (isRunning)
        {
             Message m(MessageType::TIJERAS, mainPlayer);
            socket.send(m, socket);
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