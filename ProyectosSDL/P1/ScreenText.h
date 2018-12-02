#pragma once
#include "checkML.h"
#include "ArkanoidObject.h"

typedef unsigned int uint;

class ScreenText : public ArkanoidObject {
public:
	ScreenText() {}
	ScreenText(uint w, uint h, Vector2D pos, Texture* t) :
		ArkanoidObject(w, h, pos, t) {}
	~ScreenText() {}

	void render() const {};
	void screenRender() { ArkanoidObject::render(); };
};

