#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <list>
#include "Vector2D.h"
#include "Wall.h"
#include "BlocksMap.h"
#include "Paddle.h"
#include "Ball.h"
#include "Counter.h"
#include "LifeCounter.h"
#include "LevelCounter.h"
#include "Text.h"
#include "ScreenText.h"
#include "LevelReward.h"
#include "LifeReward.h"
#include "LengthenReward.h"
#include "LaserReward.h"
#include "Laser.h"
#include "ShortenReward.h"
#include "StuckReward.h"
#include "Enemy.h"

/*
	TO-DO:
	- Reestructurar la clase game
	- Falta implementar metodos saveFromFile() y loadFromFile()
	- Falta implementar Reward
	- Comprobar que el include checkML.h están en todos los ficheros para que no haya basura (¿también en cpp?)
	- Comprobar que todos estan en #pragma once
	- Comprobar que no sobran includes
	- (Opcional) Quitar punteros de gameoverText, winText, levelcompletedText.

	PREGUNTAS:
	- ¿Cómo accedo a un objeto de la lista o hace falta tener punteros a él fuera?
	- ¿Hace falta poner posiciones, tamaños, etc. en double? (saltan muchos warnings por conversión)

	BUGS:
	- La bola atraviesa el paddle cuando se mueve muy horizontalmente.
	- A veces firstReward se pone NULL (Lasers?),
		y da error al crear un nuevo Reward
		-También en killReward -> el problema está en los if(it == firstReward)

	MEJORAS:
	- Quitar los castings (ver enunciado de la práctica)
	- Destructores virtuales?
*/

typedef unsigned int uint;

const uint NUM_TEXTURES = 15;
const uint NUM_WALLS = 3;

const uint NUM_TEMPORAL_OBJECTS = 5;

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint FRAME_RATE = 20;

const uint BALL_SIZE = 20;
const int BALL_SPEED = 10;

const uint PADDLE_WIDTH = 80;
const uint PADDLE_HEIGHT = 20;
const int PADDLE_SPEED = 10;

const uint WALL_WIDTH = 20;
const uint GAP_WIDTH = 4;

const string IMAGES_PATH = "..\\images\\";
const string LEVELS_PATH = "..\\levels\\";

const uint TOTAL_LEVELS = 3;
const uint TOTAL_LIVES = 3;

const uint HIGH_SCORE_TOP_SIZE = 10;
const uint NUM_DIGITS_SCORE = 4;
const uint NUM_DIGITS_LEVEL = 2;

const uint WALL_COLLIDES_OFFSET = 6;
const double REFLECTION = 0.25;

const int REWARD_PROBABILITY = 1;
const uint REWARD_WIDTH = 40;
const uint REWARD_HEIGHT = 20;
const int REWARD_SPEED = 3;
const uint NUM_REWARDS = 5;
const int PADDLE_MODIFY_VALUE = 50; //Paddle width modifier's constant value

const uint LASER_SIZE = 10;
const int LASER_SPEED = 10;
const uint LASER_DELAY = 40;

const int ENEMY_PROBABILITY = 5;
const int ENEMY_SPEED = 3;
const int ENEMY_WIDTH = 30;
const int ENEMY_HEIGHT = 40;

enum TextureName { SideText, TopSideText, BricksText, PaddleText, BallText, DigitsText, TimeText, GameOverText, LevelCompletedText, WinText, LevelText, YourTimeText, BestTimesText, RewardsText, EnemyText };
enum WallName { LeftWall, RightWall, TopWall };
enum RewardType { LevelRew, LifeRew, LengthenRew, ShortenRew, StuckRew, LaserRew };

struct TextureAtributes {
	string filename;
	uint nRows;
	uint nCols;
};

struct WallAtributes {
	uint w;
	uint h;
	Vector2D pos;
	Vector2D coll;
	TextureName textureName;
};

const WallAtributes wallAtrib[NUM_WALLS] = {
	{WALL_WIDTH,WIN_HEIGHT,Vector2D(GAP_WIDTH,2 * WALL_WIDTH),Vector2D(1,0),TextureName(SideText)},
	{WALL_WIDTH, WIN_HEIGHT, Vector2D(WIN_WIDTH - WALL_WIDTH - GAP_WIDTH, 2 * WALL_WIDTH),Vector2D(-1,0), TextureName(SideText)},
	{WIN_WIDTH, WALL_WIDTH, Vector2D(0, 2 * WALL_WIDTH),Vector2D(0,1), TextureName(TopSideText)} };

const TextureAtributes textureAtrib[NUM_TEXTURES] = {
	{"side.png",1,1},{"topside.png",1,1},{"bricks.png",2,3},{"paddle.png",1,1},{"ball.png",1,1},{"digits.png",3,4},{"timeText.png",1,1},
	{"gameOverText.png",1,1},{"levelCompletedText.png",1,1},{"winText.png",1,1},{"levelText.png",1,1},{"yourTimeText.png",1,1},{"bestTimesText.png",1,1},{"rewards.png",10,8},{"enemy.png",1,8} };

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	bool exit = false;
	bool gameOver = false;
	bool levelWin = false;

	uint level = 2;
	uint startTime = 0;
	uint lives = TOTAL_LIVES;

	int scores[HIGH_SCORE_TOP_SIZE];
	uint score = 0;

	list<ArkanoidObject*> objects;

	list<ArkanoidObject*>::iterator firstReward = objects.end();
	list<ArkanoidObject*>::iterator lastLevelObject = objects.end();
	uint numRewards = 0;

	BlocksMap* blocksMap = nullptr;
	Ball* ball = nullptr;
	Paddle* paddle = nullptr;
	Enemy* enemy = nullptr;

	ScreenText* gameOverText = nullptr;
	//Text* timeText = nullptr;
	//Text* levelText = nullptr;
	ScreenText* levelCompletedText = nullptr;
	ScreenText* winText = nullptr;
	Text* yourTimeText = nullptr;
	Text* bestTimesText = nullptr;

	Counter* finalScore = nullptr;
	Counter* timeCounter = nullptr;
	//Counter* levelCounter = nullptr;
	LifeCounter* lifeCounter = nullptr;
	Counter* scoreCounter[HIGH_SCORE_TOP_SIZE];

	Texture* textures[NUM_TEXTURES];
	Wall* walls[NUM_WALLS];

public:
	Game();
	~Game();

	void run();
	void render() const;

	void renderGameOver()const;
	void renderLevelCompleted()const;
	void renderWin()const;
	void renderScore()const;

	void handleEvents();
	void update();

	bool wallCollision(const SDL_Rect& rect, const Vector2D& vel, Vector2D& collVector);
	bool blocksMapCollision(const SDL_Rect& rect, const Vector2D& vel, Vector2D& collVector, bool destroy);
	bool collides(const SDL_Rect& rect, const Vector2D& vel, Vector2D& collVector);
	bool collidesPaddle(const SDL_Rect& rect);
	void levelCompleted();
	void reset();
	void youWin();
	void createObjects();
	void destroyObjects();
	void ballLost();

	void save();
	void saveConfig();
	void load();
	template <typename T>
	void loadFromConfig(T parameter);

	void saveScore();
	void loadScore();

	void createReward(const SDL_Rect& rect);

	void killObject(list<ArkanoidObject*>::iterator it);
	void killReward(list<ArkanoidObject*>::iterator it);

	void destroyRewards();

	void toggleLevelWin() { levelWin = true; };

	void lifeUp();
	void modifyPaddle(int value);
	
	void setStickyBall(bool b);
	void setStuckBall(bool b);
	bool getStickyBall();

	void setPaddleLasers(bool value);
	void createLasers();
	void setLaserInList(Laser* laser);
};


