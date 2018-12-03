#pragma once

#include "Texture.h"

typedef unsigned int uint;

class Helicopter {
private:
	uint w = 0;
	uint h = 0;
	uint x = 0; int y = 0;
	uint dirX = 0; int dirY = 0;
	uint frame = 0;
	Texture* texture;

	uint speed = 10;
	bool move = false;
public:
	Helicopter() {}
	Helicopter(uint w, uint h, uint x, uint y, Texture* t) :
		w(w), h(h), x(x), y(y), texture(t) {}
	~Helicopter() {}
	void render() const;
	void update();
	void handleEvents(SDL_Event& event);
};


