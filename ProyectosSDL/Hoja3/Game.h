#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Dog.h"
#include "Helicopter.h"

typedef unsigned int uint;

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 3;
const uint FRAME_RATE = 60;
const uint TIME_PER_FRAME = 100;

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	Dog* dog = nullptr;
	Helicopter* helicopter = nullptr;

	bool exit = false;

	Texture* textures[NUM_TEXTURES];
	SDL_Rect allRect{0,0,WIN_WIDTH,WIN_HEIGHT};

	
public:
	Game();
	~Game();
	void run();
	void render() const;
	void handleEvents();
	void update();
};
