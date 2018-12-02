#pragma once
#include "checkML.h"
#include "ArkanoidObject.h"

typedef unsigned int uint;

class Text: public ArkanoidObject {
public:
	Text() {}
	Text(uint w, uint h, Vector2D pos, Texture* t) :
		ArkanoidObject(w,h,pos,t){}
	~Text() {}
};