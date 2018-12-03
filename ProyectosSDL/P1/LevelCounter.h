#pragma once
#include "Counter.h"
class LevelCounter :
	public Counter
{
public:
	LevelCounter(Vector2D pos, uint w, uint h, uint initialNumber, uint totalDigits, Texture* t) : 
		Counter( pos,  w,  h,  initialNumber,  totalDigits, t){};
	~LevelCounter() {};


	void update() {};
};

