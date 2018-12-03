#include "Dog.h"
#include "Game.h"

void Dog::render() const{
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;
	destRect.w = w;
	destRect.h = h;

	texture->renderFrame(destRect,0,frame);
}

void Dog::update() {
	if (move) {
		x = (x + speed) % WIN_WIDTH;
		frame = (frame + 1) % texture->getNumCols();
	}
}

void Dog::handleEvents(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_d)
			move = !move;
		else if (event.key.keysym.sym == SDLK_f)
			speed += 10;
		else if (event.key.keysym.sym == SDLK_s) {
			if (speed > 10)
				speed -= 10;
		}
	}
}
