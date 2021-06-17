#include "Mapa.h"
#include "Game.h"   
#include "Player.h"


#include <algorithm>


double Mapa::endY = 200;

Mapa::Mapa(SDL_Renderer *renderer, const Vector2D &startPos, int width) : bulletFilename("./Assets/whiterect.png"), playerFilename("./Assets/player.png"),
                                                                           backgroundFilename("./Assets/cs2d.jpg"), startPos(startPos), renderer(renderer)
{
    offset = width / (N_LANES * 4);

    background = new GameObject(renderer, backgroundFilename, {startPos.x, -INITIAL_RESOLUTION_Y}, {}, {5, 5});
	
    player = new Player(renderer, playerFilename, startPos, {}, {0.5, 0.5}, width);

	clearBullets();
}

Mapa::~Mapa()
{
	clearBullets();
    delete player;
    delete background;

}

void Mapa::to_bin()
{
    startPos.to_bin();
    int dataSize = startPos.size();
   

    if (player != nullptr)
    {
        player->to_bin();
        dataSize += player->size();
    }

    if (background != nullptr)
    {
        background->to_bin();
        dataSize += background->size();
    }

  

    alloc_data(dataSize + sizeof(int));
    memcpy(_data, startPos.data(), startPos.size());
    char *aux = _data + startPos.size();

 
  
    aux += sizeof(int);

    if (player != nullptr)
    {
        memcpy(aux, player->data(), player->size());
        aux += player->size();
    }

    if (background != nullptr)
    {
        memcpy(aux, background->data(), background->size());
        aux += background->size();
    }

  
}

int Mapa::from_bin(char *data)
{
    try
    {
        startPos.from_bin(data);
        char *aux = data + startPos.size();

        int dataSize = startPos.size();

        if (player == nullptr)
            player = new Player(renderer, playerFilename);

        player->from_bin(aux);
        aux += player->size();
        dataSize += player->size();

        if (background == nullptr)
            background = new GameObject(renderer, backgroundFilename);

        background->from_bin(aux);
        aux += background->size();
        dataSize += background->size();

      

        _size = dataSize + sizeof(int);

        return 0;
    }
    catch (std::exception e)
    {
        std::cout << "Error al deserializar\n";
        return -1;
    }
}

void Mapa::update(double deltaTime)
{
    if (player != nullptr)
    {
        player->update(deltaTime);

        Vector2D vel = {0, player->getVelocity()};

        if (background != nullptr)
        {
            background->setPosition(background->getPosition() + vel * deltaTime);
            if (background->getPosition().y + 10 >= 0)
                background->setPosition({background->getPosition().x, -INITIAL_RESOLUTION_Y});
        }


    }
    checkCollisions();
}

void Mapa::render()
{
    if (background != nullptr)
        background->render();


    if (player != nullptr)
        player->render();
}

void Mapa::handleInput(Input input)
{
    if (player != nullptr)
        player->handleInput(input);
}

void Mapa::checkCollisions()
{
    int i = 0;
}

void Mapa::createBullets()
{

}

bool Mapa::raceEnded()
{
    return true;
}

void Mapa::setBulletsPosition(int width, int posY)
{
   
}

void Mapa::removeBullet()
{
  
}

void Mapa::clearBullets()
{

}