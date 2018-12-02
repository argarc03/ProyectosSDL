#pragma once

#include "checkML.h"
#include "ArkanoidObject.h"
//#include "Game.h"

typedef unsigned int uint;

class Game;

class Wall : public ArkanoidObject {
private:
	Vector2D collision = Vector2D(0, 0);
public:
	Wall() {}
	Wall(uint w, uint h, Vector2D pos, Vector2D collision, Texture* t) : ArkanoidObject(w, h, pos, t), collision(collision) {}
	~Wall() {}

	bool collides(const SDL_Rect& ballRect, const Vector2D& ballVel, Vector2D& collVector);
};

