#pragma once
#include "checkML.h"
#include "MovingObject.h"
#include "Paddle.h"
//#include "Game.h"

typedef unsigned int uint;

class Ball:public MovingObject{
private: 
	Paddle* paddle = nullptr;
	bool stuck = true;//pegado
	bool sticky = false;//pegajoso
	double paddleOffset = 0;
	bool super = false;//atraviesa
public:
	Ball() {};
	Ball(Vector2D pos, uint w, uint h, Vector2D speed, Game* game, Paddle* paddle, Texture* t) :
		MovingObject(pos, w, h, speed, game, t), paddle(paddle) {
		paddleOffset = paddle->getW() / 2 - (w / 2);
	};

	virtual ~Ball() {};

	virtual void update();

	bool getSticky() { return sticky; };
	bool getStuck() { return stuck; };
	void setSticky(bool b) { sticky = b; };
	void setStuck(bool b);
	void setSpeedUp();
	void setPaddleOffset();
	void setPaddleOffset(int value);

	bool getSuper() { return super; }
	void setSuper(bool b) { super = b; }

	Vector2D getSpeed() { return speed; };

	virtual void loadFromFile(ifstream& in);
	virtual void saveToFile(ofstream& out);
};

