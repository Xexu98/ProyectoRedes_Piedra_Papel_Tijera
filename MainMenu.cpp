#include "include/MainMenu.h"



MainMenu::MainMenu(){

}

MainMenu::~MainMenu(){

}

MainMenu::Init(){
    InitSDL();
    CrearPantalla();
    //CargarDatos();
}

void MainMenu::InitSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "Error. No se puede iniciar el sdl", SDL_GetError());
        exit(1);
    }
}

void MainMenu::CrearPantalla(){
    SDL_Window* window = SDL_CreateWindow("MyGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window)
    {
        fprintf(stderr, "Error creating window.\n");
        exit(2);
    }
}

void MainMenu::CargarDatos(){
    //funcion SDL_LoadBMP es de la libreria SDL
    imagen_  = SDL_LoadBMP ("img.bmp");
    if (imagen_ == NULL){
        fprintf(stderr, "Error al carga archivo imagen", SDL_GetError());
    }

}

void MainMenu::FreeSDLSurface(){
    SDL_FreeSurface(imagen_);
    //SDL_Quit();
}