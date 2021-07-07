#include "SDLMain.h"


SDLMain::SDLMain(){
     InitSDL();
    // CargarDatos();
}

SDLMain::~SDLMain(){

}

SDLMain::Init(){
  
}

void SDLMain::InitSDL() {
    int winX, winY; 
	winX = winY = SDL_WINDOWPOS_CENTERED;
    SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("Come&Calla", winX, winY, INITIAL_RESOLUTION_X,
		INITIAL_RESOLUTION_Y, SDL_WINDOW_SHOWN);
	  

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == NULL || renderer_ == NULL) {
		std::cout<< "Game window or renderer was null \n";
	}
}

SDLMain* SDLMain::GetInstance()
{
	if(_instance==nullptr){
    	_instance = new SDLMain();
    }
    return _instance;
}

SDL_Window* SDLMain::getWindow(){
	return window_;
}

SDL_Renderer* SDLMain::getRenderer(){
	return renderer_;
}

void SDLMain::CargarDatos(){
    //funcion SDL_LoadBMP es de la libreria SDL
    imagen_  = SDL_LoadBMP ("img.bmp");
    if (imagen_ == NULL){
        fprintf(stderr, "Error al carga archivo imagen", SDL_GetError());
    }

}

void SDLMain::destroyWindow(){
	
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);

	renderer_ = nullptr;
	window_ = nullptr;

	SDL_Quit();
}