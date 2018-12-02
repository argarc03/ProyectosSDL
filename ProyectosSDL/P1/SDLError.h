#pragma once

#include "ArkanoidError.h"

class SDLError:public ArkanoidError{
public:
	//SDLError() {};
	//~SDLError() {};

	void SDL_GetError() {};
	void IMG_GetError() {};
	void TTF_GetError() {};
};

