#include "MovingObject.h"
#include <fstream>
#include <iostream>
#include "Game.h"

void MovingObject::update() {
	pos = pos + speed;
}


void MovingObject::loadFromFile(ifstream& in) {
	ArkanoidObject::loadFromFile(in);//pos
	in >> speed;//speed
}

void MovingObject::saveToFile(ofstream& out) {
	ArkanoidObject::saveToFile(out);//pos
	out << speed << endl;//speed
}