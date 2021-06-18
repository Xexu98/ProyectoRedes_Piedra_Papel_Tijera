#include "Button.h"
#include "Game.h"

Button::Button(SDL_Renderer *renderer, std::string filename, const Vector2D &pos, const Vector2D &size, std::string msg)
	: GameObject(renderer, filename, pos, Vector2D(), size)
{
	_msg = msg;
}


void Button::handleInput(Input input)
{

	switch (input)
	{
	 case LEFTCLICK:
	//   int x = event.button.x;
	//   int y = event.button.y;
	//   if ((x > pos.x) && (x < pos.x + size.x) && (y > pos.y) && (y < pos.y + size.y)){
	// 	  //meter el mensaje que hemos pasado
	//   }
	 	break;
	}
}

