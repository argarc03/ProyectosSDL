#include "Counter.h"
#include <fstream>
#include <iostream>
#include "Game.h"


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
	/*double last = SDL_GetPerformanceCounter();
	double now = SDL_GetPerformanceCounter();
	last = now;

	double deltaTime = (now - last) / (double)SDL_GetPerformanceFrequency();

	countdown -= deltaTime;
	if (countdown <= 0) {
		number = initialNumber + 1;
		countdown = 1;
	}

	counter++;

	last = now;
	now = SDL_GetPerformanceCounter();
	double deltaTime = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());
	number = initialNumber + int(counter) * deltaTime/1000;
	*/

	if (game->isPaused())
		;//startTime += ;
	else
		number = initialNumber + SDL_GetTicks() / 1000 - startTime/1000;//number = the time that has passed since the counter was created (in seconds)
	for (uint i = 0; i < totalDigits; i++)
		digits[i] = (number%int(pow(10, totalDigits - i))) / pow(10, totalDigits - 1 - i); //Separate each number's digit and place it in the digits array
}

void Counter::loadFromFile(ifstream& in) {
	in >> number;
}

void Counter::saveToFile(ofstream& out) {
	out << number << endl;

}