#include "Button.h"
#include "Game.h"

Button::Button(SDL_Renderer *renderer, std::string filename, const Vector2D &pos, const Vector2D &size, std::string msg)
	: GameObject(renderer, filename, pos, Vector2D(), size)
{
	_msg = msg;
	position=pos;
	tam=size;
}


void Button::handleInput(Input input)
{

	switch (input)
	{
	 case LEFTCLICK:
	   int xMouse;
	   int yMouse;
	   SDL_GetGlobalMouseState(&xMouse,&yMouse);
	   if ((xMouse > position.x) && (xMouse < position.x + tam.x) && (yMouse > position.y) && (yMouse < position.y + tam.y)){
	 	  //meter el mensaje que hemos pasado
	   }
	 	break;
	}
}

