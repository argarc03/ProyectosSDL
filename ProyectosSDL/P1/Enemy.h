#pragma once
#include "MovingObject.h"
#include "ArkanoidObject.h"
#include <list>

class Enemy : public MovingObject {
private:
	uint frameRow = 0;
	uint frame = 0;

	int frameRate = 10;
	int currentTime = 0;

	int probability = 10;
	list<ArkanoidObject*>::iterator it;
public:
	Enemy() {};
	Enemy(Vector2D pos, uint w, uint h, Game* game, Texture* t) :
		MovingObject(pos, w, h, Vector2D(0, 0), game, t)  {};
	~Enemy() {};

	virtual void render() const;
	void update();
	bool collides(const SDL_Rect& ballRect, Vector2D& collVector);
	void setItList(list<ArkanoidObject*>::iterator itFR);
	void destroy();
};

