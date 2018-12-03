#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Game.h"

using namespace std;

using uint = unsigned int;

/*void firstTest() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	const uint winWidth = 800;
	const uint winHeight = 600;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	else {
		//CARGA

		//carga background
		SDL_Surface* backgroundSurface;
		SDL_Texture* backgroundTexture;
		backgroundSurface = IMG_Load("..\\images\\background1.png");
		backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
		SDL_FreeSurface(backgroundSurface);
		//carga dog
		SDL_Surface* dogSurface;
		SDL_Texture* dogTexture;
		dogSurface = IMG_Load("..\\images\\dog.png");
		dogTexture = SDL_CreateTextureFromSurface(renderer, dogSurface);
		SDL_FreeSurface(dogSurface);
		//carga helicopter
		SDL_Surface* helicopterSurface;
		SDL_Texture* helicopterTexture;
		helicopterSurface = IMG_Load("..\\images\\helicopter.png");
		helicopterTexture = SDL_CreateTextureFromSurface(renderer, helicopterSurface);
		SDL_FreeSurface(helicopterSurface);
		//creacion rect src y dest para dog
		int dogTextW, dogTextH;
		SDL_QueryTexture(dogTexture, nullptr, nullptr, &dogTextW, &dogTextH);
		int dogTextFrameW = dogTextW / 6;
		int dogTextFrameH = dogTextH / 1;
		SDL_Rect dogSrcRect, dogDestRect;
		dogSrcRect.x = dogSrcRect.y = 0;
		dogSrcRect.w = dogTextFrameW;
		dogSrcRect.h = dogTextFrameH;
		dogDestRect.x = 0;
		dogDestRect.y = 450;
		dogDestRect.w = dogDestRect.h = 100;

		//creacion rect src y dest para helicopter
		int helicopterTextW, helicopterTextH;
		SDL_QueryTexture(helicopterTexture, nullptr, nullptr, &helicopterTextW, &helicopterTextH);
		int helicopterTextFrameW = helicopterTextW / 5;
		int helicopterTextFrameH = helicopterTextH / 1;
		SDL_Rect helicopterSrcRect, helicopterDestRect;
		helicopterSrcRect.x = helicopterSrcRect.y = 0;
		helicopterSrcRect.w = helicopterTextFrameW;
		helicopterSrcRect.h = helicopterTextFrameH;
		helicopterDestRect.x = 0;
		helicopterDestRect.y = 100;
		helicopterDestRect.w = helicopterDestRect.h = 100;
		//variables globales
		int FRAME_RATE = 60;
		int TIME_PER_FRAME = 100;
		uint32_t startTime, frameTime;
		startTime = SDL_GetTicks();

		int posDog = 0;
		int posHelicopter = winWidth;

		int speedDog = 10;
		int speedHelicopter = 10;

		bool moveDog = false;
		bool moveHelicopter = false;

		bool exit = false;
		while (!exit) { // Bucle del juego
			//HANDLE EVENTS

			SDL_Event event;
			while (SDL_PollEvent(&event) && !exit) {
				if (event.type == SDL_QUIT)
					exit = true;
				else if (event.type == SDL_KEYDOWN) {
					if (event.key.keysym.sym == SDLK_h)
						moveHelicopter = !moveHelicopter;
					else if (event.key.keysym.sym == SDLK_d)
						moveDog = !moveDog;
					else if (event.key.keysym.sym == SDLK_f)
						speedDog += 10;
					else if (event.key.keysym.sym == SDLK_s) {
						if (speedDog > 10) 
							speedDog -= 10;
					}
					else if (event.key.keysym.sym == SDLK_j)
							speedHelicopter += 10;
					else if (event.key.keysym.sym == SDLK_g) {
						if (speedHelicopter > 10) 
							speedHelicopter -= 10;
					}
				}
					
			}

			frameTime = SDL_GetTicks() - startTime; // Tiempo desde última actualización
			if (frameTime >= FRAME_RATE) {
				// UPDATE
				if(moveDog) 
					posDog = (posDog + speedDog) % winWidth;
				if (moveHelicopter) 
					posHelicopter = (posHelicopter + winWidth-speedHelicopter) % winWidth;

				startTime = SDL_GetTicks();
			}

			//RENDER

			//clear
			SDL_RenderClear(renderer);
			//mover rect dog
			if (moveDog)
				dogSrcRect.x = dogTextFrameW * int(((SDL_GetTicks() / TIME_PER_FRAME) % 6));
			dogDestRect.x = posDog;
			//mover rect helicopter
			if (moveHelicopter)
				helicopterSrcRect.x = helicopterTextFrameW * int(((SDL_GetTicks() / TIME_PER_FRAME) % 5));
			helicopterDestRect.x = posHelicopter;
			//copiar al buffer
			SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
			SDL_RenderCopy(renderer, dogTexture, &dogSrcRect, &dogDestRect);
			SDL_RenderCopy(renderer, helicopterTexture, &helicopterSrcRect, &helicopterDestRect);
			//render
			SDL_RenderPresent(renderer);
			//delay
			SDL_Delay(50);
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}*/

int main(int argc, char* argv[]) {
	//firstTest();
	Game* game = new Game();
	game->run();
	return 0;
}