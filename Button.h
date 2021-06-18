#ifndef BUTTON_H
#define BUTTON_H

#include "GameObject.h"


class Button : public GameObject {
public:
	Button(SDL_Renderer *renderer = NULL, std::string filename = "", const Vector2D &pos = Vector2D(),
			const Vector2D &size = Vector2D(), std::string &msg = "");

	virtual void handleInput(Input input);
private:

std::string _msg = "";

};

#endif