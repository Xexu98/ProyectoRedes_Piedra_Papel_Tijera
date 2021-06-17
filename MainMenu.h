#include <SDL2/SDL.h>

SDL_Surface * screen_;
SDL_Surface * imagen_;

class MainMenu {

public:

MainMenu();
~MainMenu();

protected:

private:

void Inti();

void InitSDL();
void CrearPantalla();
void CargarDatos();
void FreeSDLSurface();

