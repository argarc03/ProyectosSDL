#include "Button.h"
#include "Game.h"

void Button::render() const {
	SDL_Rect destRect = getRect();

	texture->renderFrame(destRect, 0, frame);
}


void Button::handleEvent(SDL_Event& event) {
	if (event.type == SDL_MOUSEMOTION) {
		SDL_Point p = {event.motion.x, event.motion.y};

		if (SDL_PointInRect(&p, &getRect())) {
			in = true; //poner sprite de over
			frame = 1;
		}
		else {
			in = false; //poner sprite normal
			frame = 0;
		}
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (in && event.button.button == SDL_BUTTON_LEFT) {
			frame = 2;

			if (type == 0)
				g->newGame();
			else if (type == 1)
				//g->inputText();
				g->continueGame();
		}
	}
}