#pragma once

#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class ArkanoidObject : public GameObject {
protected:
	uint w = 0; uint h = 0;
	Vector2D pos = Vector2D(0, 0);

	Texture* texture = nullptr;
public:
	ArkanoidObject() {};
	ArkanoidObject(uint w, uint h, Vector2D pos, Texture* t) :w(w), h(h), pos(pos), texture(t) {};
	virtual ~ArkanoidObject() {};

	virtual void render() const;
	virtual void update() {};
	virtual void handleEvent() {};

	// Loads from file the ArkanoidObject's position
	virtual void loadFromFile(ifstream& in);
	// Loads from file the ArkanoidObject's position
	virtual void saveToFile(ofstream& out);

	SDL_Rect getRect() const;

	uint getX() const { return pos.getX(); };
	uint getY() const { return pos.getY(); };
	uint getW() const { return w; };
	void setW(uint _w) { w = _w; };
	uint getH() const { return h; };
};

