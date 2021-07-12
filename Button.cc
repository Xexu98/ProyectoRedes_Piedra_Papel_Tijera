#include "Button.h"
#include "Message.h"
#include "SDLTexture.h"

Button::Button(const char* n):nick(n)
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

SDLTexture *Button::getButtonTexture()
{
    return texture;
}

Vector2D Button::getButtonPos()
{
    return pos;
}

int16_t Button::getButtonTam()
{
    return tam;
}
