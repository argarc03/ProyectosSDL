#pragma once

#include "ArkanoidObject.h"

class Game;

class Button: public ArkanoidObject{
private:
	Game* g = nullptr;
	int frame = 0;
	bool in = false;
	int type = 0;
public:
	Button() {};
	Button(uint w, uint h, Vector2D pos, Game* g, int type, Texture* t) : ArkanoidObject(w, h, pos, t), g(g), type(type) {}
	~Button() {};

	void handleEvent(SDL_Event& event);
	void render() const;
};

