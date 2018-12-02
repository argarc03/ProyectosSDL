#ifndef GameH
#define GameH

#include "Game.h"
#include "Texture.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <time.h>

using namespace std;

Game::Game() {
	srand(time(nullptr));
	//CAMBIAR ESTO PARA PONER BOTONES EN SDL
	// We ask if there is a started game and if the user wants to continue this game or start a new game
	ifstream in;
	in.open("save.txt");
	bool partidaCargada = false;
	if (in.is_open()) {
		bool finMenu = false;
		//create window
		if (MessageBoxA(NULL, "�Deseas continuar la partida?", "Se ha encontrado una partida guardada", MB_YESNO) == IDYES) {
			finMenu = true;
			partidaCargada = true;
			MessageBoxA(NULL, "Partida cargada con �xito.\nPulsa Aceptar para continuar la partida.", "", MB_OK);
		}
		else {
			finMenu = true;
			remove("save.txt");
			MessageBoxA(NULL, "Partida guardada eliminada.\nPulsa Aceptar para empezar la nueva partida.", "", MB_OK);
		}
	}
	in.close();

	// We first initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw "Error loading the SDL window or renderer";

	// We now create the textures
	for (uint i = 0; i < NUM_TEXTURES; i++)
		textures[i] = new Texture(renderer, IMAGES_PATH + textureAtrib[i].filename, textureAtrib[i].nRows, textureAtrib[i].nCols);

	// We finally create the game objects

	//BlocksMap
	objects.push_back(new BlocksMap(Vector2D(WIN_WIDTH / 2 - (WIN_WIDTH - 2 * WALL_WIDTH - 2 * GAP_WIDTH) / 2, 6 * WALL_WIDTH + GAP_WIDTH), WIN_WIDTH - 2 * WALL_WIDTH - 2 * GAP_WIDTH, WIN_HEIGHT / 2));
	blocksMap = dynamic_cast<BlocksMap*>(*(--(objects.end())));


	//Walls
	for (uint i = 0; i < NUM_WALLS; i++) {
		objects.push_back(new Wall(wallAtrib[i].w, wallAtrib[i].h, wallAtrib[i].pos, wallAtrib[i].coll, textures[wallAtrib[i].textureName]));
		walls[i] = dynamic_cast<Wall*>(*(--(objects.end())));
	}

	//TimeText
	objects.push_back(new Text(4 * WALL_WIDTH, 2 * WALL_WIDTH, Vector2D(0, 0), textures[TextureName(TimeText)]));
	//LevelText
	objects.push_back(new Text(4 * WALL_WIDTH, 2 * WALL_WIDTH, Vector2D(WIN_WIDTH / 2 + 12 * WALL_WIDTH, 0), textures[TextureName(LevelText)]));

	//Enemy
	objects.push_back(new Enemy(Vector2D(WIN_WIDTH / 2, 3 * WALL_WIDTH + GAP_WIDTH), ENEMY_WIDTH, ENEMY_HEIGHT, this, textures[TextureName(EnemyText)]));
	enemy = dynamic_cast<Enemy*>(*(--(objects.end())));

	//GameOverText
	objects.push_back(new ScreenText(14 * WALL_WIDTH, 4 * WALL_WIDTH, Vector2D(WIN_WIDTH / 2 - 7 * WALL_WIDTH, WIN_HEIGHT / 2 - 2 * WALL_WIDTH), textures[TextureName(GameOverText)]));
	gameOverText = dynamic_cast<ScreenText*>(*(--(objects.end())));
	//LevelCompletedText
	objects.push_back(new ScreenText(18 * WALL_WIDTH, 4 * WALL_WIDTH, Vector2D(WIN_WIDTH / 2 - 8 * WALL_WIDTH, WIN_HEIGHT / 2 - 2 * WALL_WIDTH), textures[TextureName(LevelCompletedText)]));
	levelCompletedText = dynamic_cast<ScreenText*>(*(--(objects.end())));
	//WinText
	objects.push_back(new ScreenText(14 * WALL_WIDTH, 4 * WALL_WIDTH, Vector2D(WIN_WIDTH / 2 - 7 * WALL_WIDTH, WIN_HEIGHT / 2 - 2 * WALL_WIDTH), textures[TextureName(WinText)]));
	winText = dynamic_cast<ScreenText*>(*(--(objects.end())));

	if (!partidaCargada) //New game
	{
		createObjects();
		//Load inicial del blocksmap
		blocksMap->load(LEVELS_PATH + "level" + to_string(level) + ".ark", textures[TextureName(BricksText)]);

	}
	else { 
		
		
		load();
	}

}
Game::~Game() {
	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];

	for (auto it = --(objects.end()); it != objects.begin();) {
		auto prev = it;
		--prev;
		delete *it;
		objects.erase(it);
		it = prev;
	}

	delete *objects.begin();
	objects.erase(objects.begin());

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!exit) {
		while (!exit && !levelWin && !gameOver) {
			handleEvents();
			frameTime = SDL_GetTicks() - startTime; // Tiempo desde �ltima actualizaci�n
			if (frameTime >= FRAME_RATE) {
				update();
				startTime = SDL_GetTicks();
			}
			render();
		}
		if (levelWin)
			levelCompleted();
		else if (gameOver) {
			renderGameOver();
			SDL_Delay(3000);
			exit = true;
		}
	}
	if (!levelWin && !gameOver)
		save();
}
void Game::update() {
	for (auto it = objects.begin(); it != objects.end();) {
		auto next = it;
		++next;
		(*it)->update();
		it = next;
	}


	if (ball->getY() >= WIN_HEIGHT + 2 * BALL_SIZE)//If the ball is under the paddle, it is lost
		ballLost();
}

void Game::render() const {
	SDL_RenderClear(renderer);

	for (ArkanoidObject* a : objects)
		a->render();

	SDL_RenderPresent(renderer);
}

//Render the Game Over screen when lives is 0
void Game::renderGameOver()const {
	SDL_RenderClear(renderer);

	gameOverText->screenRender();

	SDL_RenderPresent(renderer);
}

//Render the Level Completed screen when you completed a level
void Game::renderLevelCompleted() const {
	SDL_RenderClear(renderer);

	levelCompletedText->screenRender();

	SDL_RenderPresent(renderer);
}

//Render the You Win screen when you completed the game
void Game::renderWin()const {
	SDL_RenderClear(renderer);

	winText->screenRender();

	SDL_RenderPresent(renderer);
}

//Render the Score screen, with your score and the top-10 high scores
void Game::renderScore()const {
	SDL_RenderClear(renderer);

	finalScore->render();
	bestTimesText->render();
	yourTimeText->render();

	for (int i = 0; i < HIGH_SCORE_TOP_SIZE; i++)
		scoreCounter[i]->render();

	SDL_RenderPresent(renderer);
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) {
			exit = true;
		}
		paddle->handleEvents(event);
	}
}

bool Game::wallCollision(const SDL_Rect& rect, const Vector2D& vel, Vector2D& collVector) {
	if (rect.x < 2 * WALL_WIDTH) { //Left wall
		if (walls[WallName(LeftWall)]->collides(rect, vel, collVector))
			return true;
	}
	else if (rect.x + rect.w > WIN_WIDTH - 2 * WALL_WIDTH) { //Right wall
		if (walls[WallName(RightWall)]->collides(rect, vel, collVector))
			return true;
	}
	if (rect.y < 4 * WALL_WIDTH) { //Top wall
		if (walls[WallName(TopWall)]->collides(rect, vel, collVector))
			return true;
	}

	return false;
}

bool Game::blocksMapCollision(const SDL_Rect& rect, const Vector2D& vel, Vector2D& collVector, bool destroy) {
	if (rect.y < blocksMap->getY() + blocksMap->getH() + GAP_WIDTH) { //Checks that the ball is inside the limits of blocksMap
		Block* block = blocksMap->collides(rect, vel, collVector); //Gets the block the ball is colliding with 
		if (block != nullptr) {
			if (destroy) {
				blocksMap->ballHitsBlock(block);//Destroy the block

												//Create random reward (PROBABILITY = 1/5)
				int random = rand() % REWARD_PROBABILITY + 1;
				if (random == 1)
					createReward(rect);

				if (blocksMap->getNumBlocks() == 0)//Checks if the level is over
					levelWin = true;
			}	
			return true;
		}
	}

	return false;
}

//Returns true if the ball collides with an object and if there is, modifies the collVector.
bool Game::collides(const SDL_Rect& rect, const Vector2D& vel, Vector2D& collVector) {
	//BlocksMap
	if (blocksMapCollision(rect, vel, collVector, true))
		return true;
	//Walls
	if (wallCollision(rect, vel, collVector))
		return true;
	//Paddle
	if (rect.y > blocksMap->getY() + blocksMap->getH() + GAP_WIDTH) { //Checks if the ball is under blocksMap
		if (paddle->collides(rect, collVector)) {
			if (ball->getSticky()) {
				ball->setStuck(true);
				setStickyBall(false);
			}
			return true;
		}
	}
	//Enemy
	if (enemy->collides(rect, collVector))
		return true;

	return false;
}

void Game::levelCompleted() {
	if (level < TOTAL_LEVELS) { //If it's not the last level, the Level Completed screen is shown and the map loads the next level.
		renderLevelCompleted();
		SDL_Delay(2000);
		level++;

		//destroyRewards(); //Destroys the rewards

		//borro mapa
		delete *objects.begin();
		objects.erase(objects.begin());
		//creo uno nuevo
		objects.push_front(new BlocksMap(Vector2D(WIN_WIDTH / 2 - (WIN_WIDTH - 2 * WALL_WIDTH - 2 * GAP_WIDTH) / 2, 3 * WALL_WIDTH + GAP_WIDTH), WIN_WIDTH - 2 * WALL_WIDTH - 2 * GAP_WIDTH, WIN_HEIGHT / 2));
		blocksMap = dynamic_cast<BlocksMap*>(*(objects.begin()));
		blocksMap->load(LEVELS_PATH + "level" + to_string(level) + ".ark", textures[TextureName(BricksText)]);

		reset();
	}
	else { //If the level completed is the last level, the You Win screen is shown.
		exit = true;
		youWin();
		renderWin();
		SDL_Delay(2000);
		renderScore();
		SDL_Delay(4000);
	}
}

//Reset the objects in scene (paddle, ball, etc.) and update (delete and create) the counters (lifes, level, etc.).
void Game::reset() {
	destroyObjects();
	createObjects();

	levelWin = false;
}

//Update the top-10 high score and create the You Win screen objects.
void Game::youWin() {
	loadScore();
	saveScore();

	//Your Time text
	objects.push_back(new Text(10 * WALL_WIDTH, 2 * WALL_WIDTH, Vector2D(WIN_WIDTH / 2 - 10 * WALL_WIDTH, 2 * WALL_WIDTH), textures[TextureName(YourTimeText)]));
	yourTimeText = dynamic_cast<Text*>(*(--(objects.end())));

	//Final Score
	objects.push_back(new Counter(Vector2D(WIN_WIDTH / 2 + 4 * WALL_WIDTH, 2 * WALL_WIDTH), 4 * WALL_WIDTH, 2 * WALL_WIDTH, score, NUM_DIGITS_SCORE, textures[TextureName(DigitsText)]));
	finalScore = dynamic_cast<Counter*>(*(--(objects.end())));
	objects.push_back(new Text(10 * WALL_WIDTH, 2 * WALL_WIDTH, Vector2D(WIN_WIDTH / 2 - 5 * WALL_WIDTH, 5 * WALL_WIDTH), textures[TextureName(BestTimesText)]));
	bestTimesText = dynamic_cast<Text*>(*(--(objects.end())));

	for (int i = 0; i < HIGH_SCORE_TOP_SIZE; i++) {
		objects.push_back(new Counter(Vector2D(WIN_WIDTH / 2 - 2 * WALL_WIDTH, 8 * WALL_WIDTH + i * 2 * WALL_WIDTH), 4 * WALL_WIDTH, 2 * WALL_WIDTH, scores[i], NUM_DIGITS_SCORE, textures[TextureName(DigitsText)]));
		scoreCounter[i] = dynamic_cast<Counter*>(*(--(objects.end())));
	}
}

//Create the objects that changes between levels.
void Game::createObjects() {
	//paddle
	objects.push_back(new Paddle(Vector2D(WIN_WIDTH / 2 - PADDLE_WIDTH / 2, WIN_HEIGHT - 2 * WALL_WIDTH), PADDLE_WIDTH, PADDLE_HEIGHT, Vector2D(0, 0), this, textures[TextureName(PaddleText)]));
	paddle = dynamic_cast<Paddle*>(*(--(objects.end())));
	//ball
	objects.push_back(new Ball(Vector2D(WIN_WIDTH / 2 - BALL_SIZE / 2, WIN_HEIGHT - 3 * WALL_WIDTH), BALL_SIZE, BALL_SIZE, Vector2D(0, -BALL_SPEED), this, paddle, textures[TextureName(BallText)]));
	ball = dynamic_cast<Ball*>(*(--(objects.end())));
	//time counter
	objects.push_back(new Counter(Vector2D(3 * WALL_WIDTH + 2 * WALL_WIDTH, 0), 4 * WALL_WIDTH, 2 * WALL_WIDTH, startTime, NUM_DIGITS_SCORE, textures[TextureName(DigitsText)]));
	timeCounter = dynamic_cast<Counter*>(*(--(objects.end())));
	//life counter
	objects.push_back(new LifeCounter(Vector2D(WALL_WIDTH + 2 * GAP_WIDTH, WIN_HEIGHT - WALL_WIDTH + GAP_WIDTH), PADDLE_WIDTH, WALL_WIDTH - 2 * GAP_WIDTH, TOTAL_LIVES, lives, textures[TextureName(PaddleText)]));
	lifeCounter = dynamic_cast<LifeCounter*>(*(--(objects.end())));
	//level counter
	objects.push_back(new LevelCounter(Vector2D(WIN_WIDTH - 2 * WALL_WIDTH, 0), 2 * WALL_WIDTH, 2 * WALL_WIDTH, level, NUM_DIGITS_LEVEL, textures[TextureName(DigitsText)]));
	lastLevelObject = --(objects.end());
}

//Destroy the objects that changes between levels.
void Game::destroyObjects() {
	destroyRewards(); //Destroys the rewards

	for (int i = 0; i < NUM_TEMPORAL_OBJECTS; i++) {
		auto prev = lastLevelObject;
		--prev;
		delete *lastLevelObject;
		objects.erase(lastLevelObject);
		lastLevelObject = prev;
	}
	lastLevelObject = objects.end();
}

//Decreases lifes and asks if the player is still alive.
void Game::ballLost() {
	lives--;
	reset();
	if (lives == 0)
		gameOver = true;
}

//Saves the game to "save.txt".
void Game::save() {
	ofstream out;
	out.open("save.txt");

	blocksMap->save(out);						//blocksmap
	out << level << endl;						//level
	timeCounter->saveToFile(out);				//time
	out << lives << endl;						//lifes
	paddle->saveToFile(out);					//paddle
	ball->saveToFile(out);						//ball
	out << numRewards << endl;							//n� de rewards guardados
	for (auto it = firstReward; it != objects.end(); ++it) {	//rewards
		(*it)->saveToFile(out);
	}

	out.close();

	//saves the game's configuration
	saveConfig();
}

//Saves all the constant parameters of the game to "config.cfg"
void Game::saveConfig() {
	ofstream out;
	out.open("config.cfg");

	out << "NUM_TEXTURES " << NUM_TEXTURES << endl;
	out << "NUM_WALLS " << NUM_WALLS << endl;
	out << "NUM_TEMPORAL_OBJECTS " << NUM_TEMPORAL_OBJECTS << endl;
	out << "WIN_WIDTH " << WIN_WIDTH << endl;
	out << "WIN_HEIGHT " << WIN_HEIGHT << endl;
	out << "FRAME_RATE " << FRAME_RATE << endl;

	//ball
	out << "BALL_SIZE " << BALL_SIZE << endl;
	out << "BALL_SPEED " << BALL_SPEED << endl;

	//paddle
	out << "PADDLE_WIDTH " << PADDLE_WIDTH << endl;
	out << "PADDLE_HEIGHT " << PADDLE_HEIGHT << endl;
	out << "PADDLE_SPEED " << PADDLE_SPEED << endl;

	//wall
	out << "WALL_WIDTH " << WALL_WIDTH << endl;
	out << "GAP_WIDTH " << GAP_WIDTH << endl;

	//file paths
	out << "IMAGES_PATH " << IMAGES_PATH << endl;
	out << "LEVELS_PATH " << LEVELS_PATH << endl;

	//levels/lives
	out << "TOTAL_LEVELS " << TOTAL_LEVELS << endl;
	out << "TOTAL_LIVES " << TOTAL_LIVES << endl;

	//text
	out << "HIGH_SCORE_TOP_SIZE " << HIGH_SCORE_TOP_SIZE << endl;
	out << "NUM_DIGITS_SCORE " << NUM_DIGITS_SCORE << endl;
	out << "NUM_DIGITS_LEVEL " << NUM_DIGITS_LEVEL << endl;

	//collision
	out << "WALL_COLLIDES_OFFSET " << WALL_COLLIDES_OFFSET << endl;
	out << "REFLECTION " << REFLECTION << endl;

	//reward
	out << "REWARD_PROBABILITY " << REWARD_PROBABILITY << endl;
	out << "REWARD_WIDTH " << REWARD_WIDTH << endl;
	out << "REWARD_HEIGHT " << REWARD_HEIGHT << endl;
	out << "REWARD_SPEED " << REWARD_SPEED << endl;
	out << "NUM_REWARDS " << NUM_REWARDS << endl;
	out << "PADDLE_MODIFY_VALUE " << PADDLE_MODIFY_VALUE << endl;

	//laser
	out << "LASER_SIZE " << LASER_SIZE << endl;
	out << "LASER_SPEED " << LASER_SPEED << endl;
	out << "LASER_DELAY " << LASER_DELAY << endl;

	//enemy
	out << "ENEMY_PROBABILITY " << ENEMY_PROBABILITY << endl;
	out << "ENEMY_SPEED " << ENEMY_SPEED << endl;
	out << "ENEMY_WIDTH " << ENEMY_WIDTH << endl;
	out << "ENEMY_HEIGHT " << ENEMY_HEIGHT << endl;

	out.close();
}

//Loads the game from "save.txt"
void Game::load() {
	blocksMap->load("save.txt", textures[TextureName(BricksText)]); //blocksmap
	ifstream in;
	in.open("save.txt");
	string s;
	for (uint i = 0; i < blocksMap->getnRows() + 1; i++) getline(in, s); //ignore the blocksmap lines in the file
	in >> level;														//level
	in >> startTime;													//time
	in >> lives;														//lifes

	objects.push_back(new Paddle(Vector2D(WIN_WIDTH / 2 - PADDLE_WIDTH / 2, WIN_HEIGHT - 2 * WALL_WIDTH), PADDLE_WIDTH, PADDLE_HEIGHT, Vector2D(0, 0), this, textures[TextureName(PaddleText)]));
	paddle = dynamic_cast<Paddle*>(*(--(objects.end())));
	paddle->loadFromFile(in);											//paddle

	objects.push_back(new Ball(Vector2D(WIN_WIDTH / 2 - BALL_SIZE / 2, WIN_HEIGHT - 3 * WALL_WIDTH), BALL_SIZE, BALL_SIZE, Vector2D(0, 0), this, paddle, textures[TextureName(BallText)]));
	ball = dynamic_cast<Ball*>(*(--(objects.end())));
	ball->loadFromFile(in);												//ball

	//Create some stuff before loading the rewards
	//Time Counter
	objects.push_back(new Counter(Vector2D(3 * WALL_WIDTH + 2 * WALL_WIDTH, 0), 4 * WALL_WIDTH, 2 * WALL_WIDTH, startTime, NUM_DIGITS_SCORE, textures[TextureName(DigitsText)]));
	timeCounter = dynamic_cast<Counter*>(*(--(objects.end())));
	//Lives Counter
	objects.push_back(new LifeCounter(Vector2D(WALL_WIDTH + 2 * GAP_WIDTH, WIN_HEIGHT - WALL_WIDTH + GAP_WIDTH), PADDLE_WIDTH, WALL_WIDTH - 2 * GAP_WIDTH, TOTAL_LIVES, lives, textures[TextureName(PaddleText)]));
	//Level Counter
	objects.push_back(new LevelCounter(Vector2D(WIN_WIDTH - 2 * WALL_WIDTH, 0), 2 * WALL_WIDTH, 2 * WALL_WIDTH, level, NUM_DIGITS_LEVEL, textures[TextureName(DigitsText)]));
	lastLevelObject = --(objects.end());

	in >> numRewards;													//numRewards
	for (int i = 0; i < numRewards; i++)
	{
		int rewardType;
		in >> rewardType;												//new reward type
		
		Reward* r = nullptr;

		switch (rewardType) {
		case LevelRew:
			r = new LevelReward(Vector2D(0, 0), REWARD_WIDTH, REWARD_HEIGHT, Vector2D(0, REWARD_SPEED), this, textures[TextureName(RewardsText)]);
			break;
		case LifeRew:
			r = new LifeReward(Vector2D(0, 0), REWARD_WIDTH, REWARD_HEIGHT, Vector2D(0, REWARD_SPEED), this, textures[TextureName(RewardsText)]);
			break;
		case LengthenRew:
			r = new LengthenReward(Vector2D(0, 0), REWARD_WIDTH, REWARD_HEIGHT, Vector2D(0, REWARD_SPEED), this, textures[TextureName(RewardsText)]);
			break;
		case ShortenRew:
			r = new ShortenReward(Vector2D(0, 0), REWARD_WIDTH, REWARD_HEIGHT, Vector2D(0, REWARD_SPEED), this, textures[TextureName(RewardsText)]);
			break;
		case StuckRew:
			r = new StuckReward(Vector2D(0, 0), REWARD_WIDTH, REWARD_HEIGHT, Vector2D(0, REWARD_SPEED), this, textures[TextureName(RewardsText)]);
			break;
		default:
			r = new LevelReward(Vector2D(0, 0), REWARD_WIDTH, REWARD_HEIGHT, Vector2D(0, REWARD_SPEED), this, textures[TextureName(RewardsText)]);
			break;
		}

		r->loadFromFile(in);

		objects.push_back(r);
		auto itFR = --(objects.end());
		if (firstReward == objects.end())
			firstReward = itFR;
		r->setItList(itFR);
	}
	in.close();
}

template <typename T>
void Game::loadFromConfig(T parameter) {
	ifstream in;
	in.open("config.cfg");
	if (!in.is_open())
		throw "Error opening config.cfg";

	//throw "Error loading parameter from config.cfg";

	string s;
	bool found = false;
	while (!in.eof()) {
		cin >> s;
	}

	in.close();
}

//Saves the top-10 scores to "scores.txt"
void Game::saveScore() {
	score = timeCounter->getNumber(); //gets the time
	if (score < scores[HIGH_SCORE_TOP_SIZE - 1]) {//if time is inside the top-10
		scores[HIGH_SCORE_TOP_SIZE - 1] = score;
		sort(scores, scores + HIGH_SCORE_TOP_SIZE);

		ofstream out;
		out.open("score.txt");

		if (!out.is_open())
			throw "No se encuentra el fichero score.txt";
		else {
			for (int i = 0; i < HIGH_SCORE_TOP_SIZE; i++)
				out << scores[i] << endl;
		}

		out.close();
	}
}

//Loads the top-10 scores from "scores.txt".
//If it doesnt exist, it creates it and fill it with 999...9
void Game::loadScore() {
	ifstream in;
	in.open("score.txt");

	if (!in.is_open()) {
		ofstream out;
		int num = 0;
		out.open("score.txt");
		for (int j = 0; j < NUM_DIGITS_SCORE; j++)
			num += pow(10, j);
		num *= 9;

		for (int i = 0; i < HIGH_SCORE_TOP_SIZE; i++)
			scores[i] = num;
		out.close();
	}
	else {
		for (int i = 0; i < HIGH_SCORE_TOP_SIZE; i++)
			in >> scores[i];
	}

	in.close();
}

void Game::createReward(const SDL_Rect& rect) {
	Reward* r = nullptr;
	int random = rand() % NUM_REWARDS + 1; //random (1-4)
	switch (random) {
	case LevelRew:
		r = new LevelReward(Vector2D(rect.x, rect.y), REWARD_WIDTH, REWARD_HEIGHT, Vector2D(0, REWARD_SPEED), this, textures[TextureName(RewardsText)]);
		break;
	case LifeRew:
		r = new LifeReward(Vector2D(rect.x, rect.y), REWARD_WIDTH, REWARD_HEIGHT, Vector2D(0, REWARD_SPEED), this, textures[TextureName(RewardsText)]);
		break;
	case LengthenRew:
		r = new LengthenReward(Vector2D(rect.x, rect.y), REWARD_WIDTH, REWARD_HEIGHT, Vector2D(0, REWARD_SPEED), this, textures[TextureName(RewardsText)]);
		break;
	case ShortenRew:
		r = new ShortenReward(Vector2D(rect.x, rect.y), REWARD_WIDTH, REWARD_HEIGHT, Vector2D(0, REWARD_SPEED), this, textures[TextureName(RewardsText)]);
		break;
	case StuckRew:
		r = new StuckReward(Vector2D(rect.x, rect.y), REWARD_WIDTH, REWARD_HEIGHT, Vector2D(0, REWARD_SPEED), this, textures[TextureName(RewardsText)]);
		break;
	case LaserRew:
		r = new LaserReward(Vector2D(rect.x, rect.y), REWARD_WIDTH, REWARD_HEIGHT, Vector2D(0, REWARD_SPEED), this, textures[TextureName(RewardsText)]);
		break;
	default:
		r = new LevelReward(Vector2D(rect.x, rect.y), REWARD_WIDTH, REWARD_HEIGHT, Vector2D(0, REWARD_SPEED), this, textures[TextureName(RewardsText)]);
		break;
	}

	objects.push_back(r);
	auto itFR = --(objects.end());
	if (firstReward == objects.end())
		firstReward = itFR;
	r->setItList(itFR);

	numRewards++;
}


bool Game::collidesPaddle(const SDL_Rect& rect) {
	Vector2D p2 = { double(rect.x),  double(rect.y) + double(rect.h) }; // bottom-left
	Vector2D p3 = { double(rect.x) + double(rect.w),  double(rect.y) + double(rect.h) }; // bottom-right

	if (paddle->getY() <= p2.getY() && paddle->getY() + paddle->getH() > p2.getY() && paddle->getX() <= p3.getX() && paddle->getX() + paddle->getW() >= p2.getX())
		return true;
	return false;
}

//Receives an iterator pointing to an object inside objects, destroy that object and erase it from the list
void Game::killObject(list<ArkanoidObject*>::iterator it) {
	delete *it;
	objects.erase(it);
}

void Game::killReward(list<ArkanoidObject*>::iterator it) {
	if (it == firstReward)
		++firstReward; //Advance firstReward in case the firstReward is being deleted

	killObject(it);

	numRewards--;
}

//borro rewards en escena
void Game::destroyRewards() {
	for (auto it = firstReward; it != objects.end();) {
		delete *it;
		it = objects.erase(it);
	}
	firstReward = objects.end();

	numRewards = 0;
}

void Game::lifeUp() {
	if (lives < TOTAL_LIVES) {
		lives++;
		lifeCounter->addLife();
	}
}

void Game::modifyPaddle(int value) {
	setStuckBall(false);
	paddle->setLasers(false);
	paddle->modifyWidth(value);
	//ball->setPaddleOffset(value);
}

void Game::setStickyBall(bool b) {
		ball->setSticky(b);
}

void Game::setStuckBall(bool b) {
	if (ball->getStuck()) {
		ball->setStuck(b);
		if (!b)
		{
			ball->setSpeedUp(); 
			ball->setSticky(b);
		}
	}
}

bool Game::getStickyBall() {
	return ball->getSticky();
}

//Sets paddle->laser = true and deactivates other rewards
void Game::setPaddleLasers(bool value) {
	setStuckBall(false);
	// * Reset del ancho del paddle?
	paddle->setLasers(value);
}

void Game::setLaserInList(Laser* laser) {
	objects.push_back(laser);
	auto itLaser = --(objects.end());
	laser->setItList(itLaser);
}

//Creates 2 lasers at paddle's position going upwards 
void Game::createLasers() {
	//Creates the left Laser
	Laser* leftLaser = new Laser({double ( paddle->getX() + (paddle->getW() / 4)),double (paddle->getY()) }, LASER_SIZE, LASER_SIZE, { 0, -LASER_SPEED }, this, textures[BallText]);
	setLaserInList(leftLaser);
	//Creates the right Laser
	Laser* rightLaser = new Laser({ double (paddle->getX() + (paddle->getW() - (paddle->getW() / 4))),double(paddle->getY()) }, LASER_SIZE, LASER_SIZE, { 0, -LASER_SPEED }, this, textures[BallText]);
	setLaserInList(rightLaser);
}
#endif
