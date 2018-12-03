#pragma once
#include "MovingObject.h"
#include "ArkanoidObject.h"
#include <list>
class Laser :
	public MovingObject
{
private:
	list<ArkanoidObject*>::iterator it; //iterator que apuntará a su posición en la lista
public:
	Laser() {};
	Laser(Vector2D pos, uint w, uint h, Vector2D speed, Game* g, Texture* t) :
		MovingObject(pos, w, h, speed, g, t) {};
	virtual ~Laser() {};

	virtual void update();
	void setItList(list<ArkanoidObject*>::iterator it);
};