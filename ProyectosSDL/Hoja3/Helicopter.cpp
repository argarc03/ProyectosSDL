#include "Helicopter.h"
#include "Game.h"

void Helicopter::render() const {
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;
	destRect.w = w;
	destRect.h = h;

	texture->renderFrame(destRect,0,frame);
}

void Helicopter::update() {
	if (move) {
		x = (x + WIN_WIDTH - speed) % WIN_WIDTH;
		frame = (frame + 1) % texture->getNumCols();
	}
}

void Helicopter::handleEvents(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_h)
			move = !move;
		else if (event.key.keysym.sym == SDLK_j)
			speed += 10;
		else if (event.key.keysym.sym == SDLK_g) {
			if (speed > 10)
				speed -= 10;
		}
	}
}
