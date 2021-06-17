#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "Mapa.h"
#include <vector>

#include <map>

#include "GameObject.h"

class Track;
class Player;

const int N_LANES = 5;
const int INITIAL_RESOLUTION_X = 1024;
const int INITIAL_RESOLUTION_Y = 720;

class Game : public Serializable
{
private:
    double startY;
    double endY;

   

    int nPlayers;
    int winner;

    SDL_Renderer *renderer;


    std::vector<Mapa*> tracks;

public:
    Game();
    Game(SDL_Renderer *r);
    ~Game();

    virtual void to_bin();
    virtual int from_bin(char *data);

    void start();
    void update(double deltaTime);
    void render();
    void handleInput(int i, Input input);

    bool collisionWithObstacle(GameObject *obj);
    bool raceEnded();

    void removeTrack(Mapa *track);
    void clearTracks();
};

#endif