#include "Counter.h"
#include <fstream>
#include <iostream>

void Counter::render() const {
	SDL_Rect destRect;
	destRect.y = pos.getY();
	destRect.h = h;

	uint digitW = w / totalDigits;

	destRect.w = digitW;
	for (uint i = 0; i < totalDigits; i++) {
		destRect.x = pos.getX() + digitW * i;
		texture->renderFrame(destRect, digits[i] / (texture->getNumCols()), digits[i] % (texture->getNumCols()));
	}
}

void Counter::update() {
	number = initialNumber + SDL_GetTicks() / 1000;//number = the time that has passed since the counter was created (in seconds)
	for (uint i = 0; i < totalDigits; i++)
		digits[i] = (number%int(pow(10, totalDigits - i))) / pow(10, totalDigits - 1 - i); //Separate each number's digit and place it in the digits array
}

void Counter::loadFromFile(ifstream& in) {
	in >> number;
}

void Counter::saveToFile(ofstream& out) {
	out << number << endl;

}