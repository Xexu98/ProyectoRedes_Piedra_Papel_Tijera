#ifndef SDLMAIN_H
#define SDLMAIN_H 

#include <SDL2/SDL.h>



class SDLMain {

    public:
    const int INITIAL_RESOLUTION_X = 1024;
    const int INITIAL_RESOLUTION_Y = 720;

    SDLMain();
    ~SDLMain();

    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();

    SDLMain(SDLMain &other) = delete;
    void operator=(const SDLMain &) = delete;

    static SDLMain* getIstance();

    void destroyWindow();
    
    protected:

    private:

    static SDLMain* _instance;

    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;

    SDL_Surface * screen_;
    SDL_Surface * imagen_;

    void InitSDL();
    void CargarDatos();

}

#endif