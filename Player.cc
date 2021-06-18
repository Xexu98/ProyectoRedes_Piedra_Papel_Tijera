#include "Player.h"
#include "Game.h"

Player::Player(SDL_Renderer *renderer, std::string filename, const Vector2D &pos, const Vector2D &rot, const Vector2D &size, int width)
	: GameObject(renderer, filename, pos, rot, size)
{
}

void Player::update(double deltaTime)
{	
		int x, y;
		SDL_GetMouseState(&x, &y);
}

void Player::handleInput(Input input)
{
	switch (input)
	{
	case LEFT:
		//moveLane(Vector2D(0,-1));
		break;
	case RIGHT:
		//moveLane(Vector2D(0, -1));
		break;
	case UP:
		//moveLane(Vector2D(1, 0));
		break;
	case DOWN:
	//	moveLane(Vector2D(-1, 0));
		break;
	default:
		break;
	}
}

