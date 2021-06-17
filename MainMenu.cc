#include "MainMenu.h"



MainMenu::MainMenu(){

}

MainMenu::~MainMenu(){

}

MainMenu::Init(){
    InitSDL();
    CrearPantalla();
    CargarDatos();
}

void MainMenu::InitSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Error. No se puede iniciar el subsistema SDL video", SDL_GetError());
        exit(1);
    }
}

void MainMenu::CrearPantalla(){
    screen_ = SDL_SetVideoMode(800, 600, 32, SDL_SWURFACE);
    if (screen_ == NULL){
        fprintf(stderr, "Error al crear la pantalla", SDL_GetError());
        exit(1);
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
    SDL_FreeSUrface(imagen_);
    //SDL_Quit();
}