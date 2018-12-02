#include "LifeCounter.h"

void LifeCounter::render() const {
	SDL_Rect destRect;
	destRect.y = getY();
	destRect.h = getH();

	uint lifeW = getW() / totalLives; //lifeW = width of life icon

	destRect.w = lifeW;
	for (int i = 0; i < lives; i++) {
		destRect.x = getX() + lifeW * i; //place its life one next to the other
		texture->render(destRect);
	}

}

void LifeCounter::addLife() {
	lives++;
}
