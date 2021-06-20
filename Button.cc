#include "Button.h"
#include "Game.h"
#include <iostream>

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
	   SDL_GetMouseState(&xMouse,&yMouse);
	   if ((xMouse > position.x) && (xMouse < position.x + tam.x) && (yMouse > position.y) && (yMouse < position.y + tam.y)){
	 	  
		   
	   }
	 	break;
	}
}

