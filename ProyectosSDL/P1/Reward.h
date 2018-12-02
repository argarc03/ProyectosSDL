#pragma once
#include "checkML.h"
#include "MovingObject.h"
#include "ArkanoidObject.h"
#include <list>

class Reward : public MovingObject {
private:
	uint frame = 0;
protected:
	uint type = 0;
	
	list<ArkanoidObject*>::iterator it; //= null??
public:
	Reward() {};
	Reward(Vector2D pos, uint w, uint h, Vector2D speed, uint prize, Game* g, Texture* t) :
		MovingObject(pos, w, h, speed, g, t), type(prize) {};
	virtual ~Reward() {};

	virtual void render() const;
	virtual void update();

	virtual void act() {};

	void setItList(list<ArkanoidObject*>::iterator itFR);

	virtual void loadFromFile(ifstream& in);

	virtual void saveToFile(ofstream& out);

	uint getType() { return type; }
};

