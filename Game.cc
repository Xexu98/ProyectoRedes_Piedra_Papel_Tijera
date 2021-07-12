#include "Game.h"
#include "Message.h"
#include "Resources.h"
#include "InputManager.h"
#include "Constants.h"

void Game::initGame()
{
    //Mandamos mensaje de login
    Message logMsg = Message(MessageType::LOGIN,bPiedra);

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

   
    bPapel = new Button(n);
    bTijeras = new Button(n);
    bPiedra= new Button(n);
    bPapel->setTexture(app->getTextureManager()->getTexture(Resources::TextureId::Papel));
    bPapel->setPosition(Vector2D(200,300));
    bPapel->setTam(1);
    bTijeras->setTexture(app->getTextureManager()->getTexture(Resources::TextureId::Tijeras));
    bTijeras->setPosition(Vector2D(400,300));
    bTijeras->setTam(1);   
    bPiedra->setTexture(app->getTextureManager()->getTexture(Resources::TextureId::Piedra));
    bPiedra->setPosition(Vector2D(0,300));
    bPiedra->setTam(1);
    background = app->getTextureManager()->getTexture(Resources::TextureId::Escenario);
}

Game::~Game()
{
    delete bPiedra;
    delete bPapel;
    delete bTijeras;
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
            ObjectInfo obj=em.getObjectInfo();
            if (em.getNick() != bPiedra->getNick())
            {
               jugadores[em.getNick()]=obj;
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
            Message m(MessageType::PIEDRA,bPiedra);
            socket.send(m, socket);
            waitingResult=true;
        }
        
    }
    if (HandleEvents::instance()->isKeyDown(SDL_SCANCODE_2))
    {
      if (isRunning)
        {
           Message m(MessageType::PAPEL,bPapel);
            socket.send(m, socket);
             waitingResult=true;
        }
    }
    if (HandleEvents::instance()->isKeyDown(SDL_SCANCODE_3) )
    {
       if (isRunning)
        {
            Message m(MessageType::TIJERAS,bTijeras);
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
    
    //Pintamos los botones

    bPapel->getButtonTexture()->render({(int)bPapel->getButtonPos().getX(),
                                            (int)bPapel->getButtonPos().getY(),
                                            bPapel->getButtonTam(),
                                            bPapel->getButtonTam()});
    bTijeras->getButtonTexture()->render({(int)bTijeras->getButtonPos().getX(),
                                            (int)bTijeras->getButtonPos().getY(),
                                            bTijeras->getButtonTam(),
                                            bTijeras->getButtonTam()});
    bPiedra->getButtonTexture()->render({(int)bPiedra->getButtonPos().getX(),
                                            (int)bPiedra->getButtonPos().getY(),
                                            bPiedra->getButtonTam(),
                                            bPiedra->getButtonTam()});

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