#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <list>

#include "Button.h"

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
#include "Laser.h"
#include "LaserReward.h"
#include "ShortenReward.h"
#include "StuckReward.h"
#include "SuperReward.h"
#include "MultipleReward.h"
#include "Enemy.h"

/*
	NOTAS:
	- LA MULTIPLICACION DE BOLAS NO FUNCIONA. HABRIA QUE CONSIDERAR LOS PUNTEROS DE BALL2 Y BALL3 AL IGUAL QUE SE HACE CON EL DE
	  BALL. ADEMAS, SE DEBERIAN DE GUARDAR LA POSICION DE LAS OTRAS BOLAS CREADAS.
	- ARREGLAR COUNTER, PUES SIGUE CORRIENDO AUNQUE ESTES EN PAUSA O EN EL MENU.

	TO-DO:
	- Falta implementar Reward
	- Comprobar que el include checkML.h están en todos los ficheros para que no haya basura (¿también en cpp?)
	- Comprobar que todos estan en #pragma once
	- Comprobar que no sobran includes
	- Resolver warnings

	PREGUNTAS:

	BUGS:
	- La bola atraviesa el paddle cuando se mueve muy horizontalmente.
*/

typedef unsigned int uint;

const uint NUM_TEXTURES = 19;
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

const int REWARD_PROBABILITY = 100;
const uint REWARD_WIDTH = 40;
const uint REWARD_HEIGHT = 20;
const int REWARD_SPEED = 3;
const uint NUM_REWARDS = 8;
const int PADDLE_MODIFY_VALUE = 50; //Paddle width modifier's constant value

const uint LASER_WIDTH = 7;
const uint LASER_HEIGHT = 23;
const int LASER_SPEED = 10;
const uint LASER_DELAY = 40;

const int ENEMY_PROBABILITY = 50;
const int ENEMY_SPEED = 3;
const int ENEMY_WIDTH = 30;
const int ENEMY_HEIGHT = 40;

enum TextureName { SideText, TopSideText, BricksText, PaddleText, BallText, DigitsText, TimeText,
	GameOverText, LevelCompletedText, WinText, LevelText, YourTimeText, BestTimesText, RewardsText,
	EnemyText, NewGameButtonText, TitleText, ContinueGameButtonText, LaserText };
enum WallName { LeftWall, RightWall, TopWall };
enum RewardType { LevelRew, LifeRew, LengthenRew, ShortenRew, StuckRew, SuperRew, MultipleRew, LaserRew };

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
	{"gameOverText.png",1,1},{"levelCompletedText.png",1,1},{"winText.png",1,1},{"levelText.png",1,1},{"yourTimeText.png",1,1},{"bestTimesText.png",1,1},
	{"rewards.png",10,8},{"enemy.png",1,8}, {"newGameButton.png",1,3}, {"title.png",1,1}, {"continueGameButton.png",1,3}, {"laser.png",1,1} };

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	bool finMenu = false;
	bool partidaCargada = false;

	bool exit = false;
	bool gameOver = false;
	bool levelWin = false;

	bool paused = false;

	uint level = 1;
	uint startTime = 0;
	uint lives = TOTAL_LIVES;

	uint numBalls = 1;

	int scores[HIGH_SCORE_TOP_SIZE];
	uint score = 0;

	list<ArkanoidObject*> objects;

	list<ArkanoidObject*>::iterator firstReward = objects.end();
	list<ArkanoidObject*>::iterator lastLevelObject = objects.end();
	uint numRewards = 0;

	Text* title = nullptr;
	Button* newGameButton = nullptr;
	Button* continueGameButton = nullptr;

	BlocksMap* blocksMap = nullptr;
	Ball* ball = nullptr;
	Ball* ball2 = nullptr;
	Ball* ball3 = nullptr;
	Paddle* paddle = nullptr;
	Enemy* enemy = nullptr;
	uint numEnemies = 0;

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

	void handleEventsMenu();

	void renderMenu();

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
	void ballLost(Ball* b);

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

	void setSuperBall(bool b);

	void multiplyBall();

	void newGame();
	void continueGame();

	void inputText();

	bool isPaused() { return paused; };
	//bool ballInside

	void spawnEnemy();
};


