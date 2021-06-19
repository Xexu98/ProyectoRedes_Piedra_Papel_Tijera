#ifndef MAP_H
#define MAP_H

#include "GameObject.h"
#include "Button.h"

#include <vector>

class Player;


const int MIN_O_DIST = 50;
const int MAX_O_DIST = 100;

class Mapa : public Serializable
{


public:
    Mapa(SDL_Renderer *renderer, const Vector2D &startPos = Vector2D(), int width = 0);
    ~Mapa();

    virtual void to_bin();
    virtual int from_bin(char *data);

    void update(double deltaTime);
    void render();
    void handleInput(Input input);
    void changeState();
    bool returnState(){return _menuInicial;}
  

private:

    void renderMenuInicial();
    void renderMenuJuego();
    

    static std::vector<Vector2D> obstaclesBasePos;
    static double endY;


    GameObject *background;
    GameObject *backgroundG;
    //botones del interfaz
    Button *playB;
    Button *quitB;
    //botones de juego
    Button *siccorB;
    Button *rockB;
    Button *paperB;


    std::string msgB;

    std::string playFilename;
    std::string quitFilename;
    std::string siccorFilename;
    std::string rockFilename;
    std::string paperFilename;
    std::string backgroundFilename;
    std::string backgroundGFilename;
  

    int offset;
    Vector2D startPos;

    SDL_Renderer *renderer;

    bool _menuInicial;

};

#endif