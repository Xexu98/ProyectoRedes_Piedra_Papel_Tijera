#include "Button.h"
#include "Message.h"
#include "SDLTexture.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::setPosition(const Vector2D &newPos)
{
    pos = newPos;
}

void Button::setTam(int16_t newTam)
{
    tam = newTam;
}

void Button::setTexture(SDLTexture *newTexture)
{
    texture = newTexture;
}

SDLTexture *Button::getPlayerTexture()
{
    return texture;
}

Vector2D Button::getPlayerPos()
{
    return pos;
}

int16_t Button::getPlayerTam()
{
    return tam;
}
