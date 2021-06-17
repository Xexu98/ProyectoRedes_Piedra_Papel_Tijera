#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject
{
private:
	int lane;
	bool hit;

	double velocity;
	double timer;
	double life = 100;
	double laneWidth;
	bool slowed;
	float slowTime;
	void move(Vector2D dir);

public:
	Player(SDL_Renderer *renderer = NULL, std::string filename = "", const Vector2D &pos = Vector2D(),
		const Vector2D &rotation = Vector2D(), const Vector2D &size = Vector2D(), int width = 0);

	virtual void update(double deltaTime);
	virtual void handleInput(Input input);

	void lessLife();

	void setVelocity(double v);
	double getVelocity() const;
};

#endif