#pragma once
#include "checkML.h"
#include "MovingObject.h"

typedef unsigned int uint;

class Paddle: public MovingObject{
private:
	bool movingLeft = false;
	bool movingRight = false;
	bool lasers = false;
	uint32_t laserTimer = 0;

public:
	Paddle() {};
	Paddle(Vector2D pos, uint w, uint h, Vector2D speed, Game* game, Texture* t) :
		MovingObject(pos, w, h, speed, game, t) {};
	virtual ~Paddle() {};
	
	virtual void update();
	virtual void handleEvents(SDL_Event& event);

	bool collides(const SDL_Rect& ballRect, Vector2D& collVector);

	void modifyWidth(int value);

	Vector2D getSpeed() { return speed; };

	bool inside();
	
	void setLasers(bool value) { 
		lasers = value;
		laserTimer = 0; //Stores in laserStartTime the time at which the lasers started
	};
};

