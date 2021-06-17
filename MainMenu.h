#ifndef MAINMENU_H
#define MAINMENU_H 

#include <SDL2/SDL.h>

class MainMenu {

public:

MainMenu();
~MainMenu();

protected:

private:

SDL_Surface * screen_;
SDL_Surface * imagen_;

void Inti();

void InitSDL();
void CrearPantalla();
void CargarDatos();
void FreeSDLSurface();
}

#endif