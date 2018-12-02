#pragma once

#include "ArkanoidObject.h"

class Game;

class MovingObject : public ArkanoidObject {
protected:
	Vector2D speed = Vector2D(0, 0);
	Game* game = nullptr;
public:
	MovingObject() {};
	MovingObject(Vector2D pos, uint w, uint h, Vector2D speed, Game* game, Texture* t)
		:ArkanoidObject(w, h, pos, t), speed(speed), game(game) {};
	virtual ~MovingObject() {};

	void update();

	// Loads from file the ArkanoidObject's speed
	virtual void loadFromFile(ifstream& in);
	// Saves in a file the ArkanoidObject's speed
	virtual void saveToFile(ofstream& out);

};
