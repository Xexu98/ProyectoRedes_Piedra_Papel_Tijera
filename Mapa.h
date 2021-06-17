#ifndef MAP_H
#define MAP_H

#include "GameObject.h"

#include <vector>

class Player;


const int MIN_O_DIST = 50;
const int MAX_O_DIST = 100;

class Mapa : public Serializable
{
private:
    static std::vector<Vector2D> obstaclesBasePos;
    static double endY;

   

    Player *player;

    GameObject *background;

    std::string bulletFilename;
    std::string playerFilename;
    std::string backgroundFilename;
  

    int offset;
    Vector2D startPos;

    SDL_Renderer *renderer;

public:
    Mapa(SDL_Renderer *renderer, const Vector2D &startPos = Vector2D(), int width = 0);
    ~Mapa();

    virtual void to_bin();
    virtual int from_bin(char *data);

    void update(double deltaTime);
    void render();
    void handleInput(Input input);

    void createBullets();
    void checkCollisions();

    static void setBulletsPosition(int width, int posY);

    bool raceEnded();

    void removeBullet();
    void clearBullets();
};

#endif