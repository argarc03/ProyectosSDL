#include "Button.h"

void Button::handleEvents(SDL_Event& event) {
	if (event.type == SDL_MOUSEMOTION) {
		SDL_Point p = {event.motion.x, event.motion.y};

		if (SDL_PointInRect(&p, &getRect()))
			in = true; //poner sprite de over
		else
			in = false; //poner sprite normal
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (in && event.button.button == SDL_BUTTON_LEFT)
			act();
	}
}