#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector2D.h"
#include "Texture.h"

#include <iostream>

enum Input
{
    LEFTCLICK,
    NONE
};

class GameObject : public Serializable
{
protected:

    Vector2D position;
    Vector2D rotation;
    Vector2D area;

    Texture *texture;

    bool isInside(const Vector2D &pos);

public:
    GameObject(SDL_Renderer *renderer = NULL, std::string filename = "", const Vector2D &pos = Vector2D(),
               const Vector2D &rotation = Vector2D(), const Vector2D &area = Vector2D(1, 1));
    GameObject(GameObject *g);         
    ~GameObject();

    virtual void to_bin();
    virtual int from_bin(char *data);

    virtual void update(double deltaTime){};
    virtual void render();
    virtual void handleInput(Input input){};

    bool overlaps(GameObject *other);
    Texture *getTexture();
    Vector2D getPosition();
    Vector2D getRotation();
    Vector2D getSize();

    void setPosition(const Vector2D &pos);
    void setRotation(const Vector2D &rot);
    void setSize(const Vector2D &s);
};

#endif