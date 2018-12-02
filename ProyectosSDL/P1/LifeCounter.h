#pragma once

#include "checkML.h"
#include "ArkanoidObject.h"

typedef unsigned int uint;

class LifeCounter: public ArkanoidObject{
private:
	uint totalLives = 0;
	uint lives = 0;
public:
	LifeCounter(Vector2D pos, uint w, uint h,uint totalLives, uint lives, Texture* t) : ArkanoidObject(w,h,pos,t), totalLives(totalLives), lives(lives) {};
	~LifeCounter() {};

	void render() const;
	void addLife();

};

