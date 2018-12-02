#pragma once

#include "ArkanoidObject.h"
#include <functional>

class Button: public ArkanoidObject{
private:
	function<void()> act = nullptr;
	bool in = false;
public:
	Button() {};
	Button(uint w, uint h, Vector2D pos, function<void()> act, Texture* t) : ArkanoidObject(w, h, pos, t), act(act) {}
	~Button() {};

	void handleEvents(SDL_Event& event);
};

