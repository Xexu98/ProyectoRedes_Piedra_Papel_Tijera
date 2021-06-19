#ifndef BUTTON_H
#define BUTTON_H

#include "GameObject.h"
#include <string.h>
#include <string>


class Button : public GameObject {
private:
	Vector2D position;
	Vector2D tam;
public:
	Button(SDL_Renderer *renderer = NULL, std::string filename = "", const Vector2D &pos = Vector2D(),const Vector2D &size = Vector2D(), std::string msg = "" );

	virtual void handleInput(Input input);
private:
std::string _msg = "";

};

#endif