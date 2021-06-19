#include "Mapa.h"
#include "Game.h"   
#include <string.h>
#include <string>

#include <algorithm>


double Mapa::endY = 200;

Mapa::Mapa(SDL_Renderer *renderer, const Vector2D &startPos, int width) : playFilename("./Assets/play_button.png"), quitFilename("./Assets/quit_button.png"),
                                                                           backgroundFilename("./Assets/mainMenu.png"),
                                                                           siccorFilename("./Assets/tijeras.png"),rockFilename("./Assets/piedra.png")
                                                                           ,paperFilename("./Assets/papel.png"),startPos(startPos), renderer(renderer)
{ 
    //offset = width / (N_LANES * 4);
    background = new GameObject(renderer, backgroundFilename, {startPos.x, -INITIAL_RESOLUTION_Y}, {5, 5});
    msgB="PLAY";
    playB = new Button(renderer, playFilename, {INITIAL_RESOLUTION_X/2, INITIAL_RESOLUTION_Y/2 + 2},{1, 1},msgB);
    msgB="QUIT";
    quitB = new Button(renderer, quitFilename, {INITIAL_RESOLUTION_X/2, INITIAL_RESOLUTION_Y/2 - 2}, {1, 1},msgB);
    msgB="SICCOR";
    siccorB = new GameObject(renderer, siccorFilename, {INITIAL_RESOLUTION_X/2 - 2 , INITIAL_RESOLUTION_Y/3}, {1, 1},msgB);
    msgB="ROCK";
    rockB = new GameObject(renderer, rockFilename, {INITIAL_RESOLUTION_X/2 , INITIAL_RESOLUTION_Y/3},  {1, 1},msgB);
    msgB="PAPER";
    paperB = new GameObject(renderer, paperFilename, {INITIAL_RESOLUTION_X/2 +2, INITIAL_RESOLUTION_Y/3}, {1, 1}, msgB);
	
    //player = new Player(renderer, playerFilename, startPos, {}, {0.5, 0.5}, width);
    
    //por defecto se incializa la app en el menu inicial de juego
    _menuInicial = true;

	
}

Mapa::~Mapa()
{

    delete playB;
    delete quitB;
    delete siccorB;
    delete rockB;
    delete paperB;
    delete background;

}

void Mapa::to_bin()
{
    startPos.to_bin();
    int dataSize = startPos.size();
   

    if (playB != nullptr)
    {
        playB->to_bin();
        dataSize += playB->size();
    }

    if (quitB != nullptr)
    {
        quitB->to_bin();
        dataSize += quitB->size();
    }

    if (siccorB != nullptr)
    {
        siccorB->to_bin();
        dataSize += siccorB->size();
    }  bool menuInicial() {
        return true;
    }


    if (paperB != nullptr)
    {
        paperB->to_bin();
        dataSize += paperB->size();
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

    if (playB != nullptr)
    {
        memcpy(aux, playB->data(), playB->size());
        aux += playB->size();
    }
     if (quitB != nullptr)
    {
        memcpy(aux, quitB->data(), quitB->size());
        aux += quitB->size();
    }
     if (siccorB != nullptr)
    {
        memcpy(aux, siccorB->data(), siccorB->size());
        aux += siccorB->size();
    }
     if (rockB != nullptr)
    {
        memcpy(aux, rockB->data(), rockB->size());
        aux += rockB->size();
    }
     if (paperB != nullptr)
    {
        memcpy(aux, paperB->data(), paperB->size());
        aux += paperB->size();
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

        if (playB == nullptr)
            playB = new Button(renderer, playFilename);

        playB->from_bin(aux);
        aux += playB->size();
        dataSize += playB->size();

         if (quitB == nullptr)
            quitB = new Button(renderer, quitFilename);

        quitB->from_bin(aux);
        aux += quitB->size();
        dataSize += quitB->size();

            if (quitB == nullptr)
            quitB = new Button(renderer, quitFilename);

        siccorB->from_bin(aux);
        aux += siccorB->size();
        dataSize += siccorB->size();

            if (quitB == nullptr)
            quitB = new Button(renderer, quitFilename);

        rockB->from_bin(aux);
        aux += rockB->size();
        dataSize += rockB->size();

            if (quitB == nullptr)
            quitB = new Button(renderer, quitFilename);

        paperB->from_bin(aux);
        aux += paperB->size();
        dataSize += paperB->size();

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
    
      
}

void Mapa::render()
{
    if (background != nullptr)
        background->render(); 


    if (_menuInicial){
        renderMenuInicial();
    }
    else{
        renderMenuJuego();
    }
}

void Mapa::handleInput(Input input)
{
    
}

void Mapa::renderMenuInicial(){
    if (playB != nullptr)
        playB->render();

    if (quitB != nullptr)
        quitB->render();
}

void Mapa::renderMenuJuego(){
    if (siccorB != nullptr)
        siccorB->render();

    if (rockB != nullptr)
        rockB->render();

    if (paperB != nullptr)
        paperB->render();
}

void Mapa::changeState()
{
    _menuInicial=!_menuInicial;
    SDL_RenderClear(renderer);
}
