#pragma once
#include "Vector2D.h"
#include <SDL2/SDL.h>
#include <string>
class SDLTexture;
 
class Button{
private:

    SDLTexture* texture = nullptr;
    Vector2D pos;
    int16_t tam;

public:
  
    Button();
    ~Button();

    //std::string getNick(){return nick;}

    SDLTexture* getButtonTexture();
    Vector2D getButtonPos();
    int16_t getButtonTam();

    void setPosition(const Vector2D& newPos);
    void setTam(int16_t newTam);
    void setTexture(SDLTexture* newTexture);

};