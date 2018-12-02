#include "ArkanoidObject.h"
#include <iostream>
#include <fstream>
#include "Vector2D.h"

void ArkanoidObject::render() const {
	SDL_Rect destRect = getRect();
	texture->render(destRect);
}

void ArkanoidObject::loadFromFile(ifstream& in) {
	in >> pos;
}

void ArkanoidObject::saveToFile(ofstream& out) {
	out << pos << endl;
}

SDL_Rect ArkanoidObject::getRect() const {
	SDL_Rect destRect;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.w = w;
	destRect.h = h;

	return destRect;
}
