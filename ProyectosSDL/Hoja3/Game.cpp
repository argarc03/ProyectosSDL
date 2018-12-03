#include "Game.h"
#include "Texture.h"

Game::Game() {
	// We first initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw "Error loading the SDL window or renderer";
	// We now create the textures
	/*for (uint i = 0; i < NUM_TEXTURES; i++) {
		
	}*/
	textures[0] = new Texture(renderer, "..\\images\\background1.png", 1, 1);
	textures[1] = new Texture(renderer, "..\\images\\dog.png", 1, 6);
	textures[2] = new Texture(renderer, "..\\images\\helicopter.png", 1, 5);
	// We finally create the game objects
	dog = new Dog(100,100,0,450,textures[1]);
	helicopter = new Helicopter(100,100,WIN_WIDTH,100, textures[2]);
}
Game::~Game() {
	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!exit) {
		handleEvents();
		frameTime = SDL_GetTicks() - startTime; // Tiempo desde última actualización
		if (frameTime >= FRAME_RATE) {
			update();
			startTime = SDL_GetTicks();
		}
		render();
		SDL_Delay(FRAME_RATE);
	}
}
void Game::update() {
	dog->update();
	helicopter->update();
}
void Game::render() const {
	SDL_RenderClear(renderer);

	textures[0]->render(allRect);
	dog->render();
	helicopter->render();

	SDL_RenderPresent(renderer);
}
void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT)
			exit = true;

		helicopter->handleEvents(event);
		dog->handleEvents(event);
		
	}
}