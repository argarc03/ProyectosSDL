#include "Ball.h"
#include "Game.h"
#include <iostream>
#include <fstream>

using namespace std;

void Ball::update() {
	Vector2D prevPos = pos; //Position before applying the movement
	if (stuck) {
		pos = { double (paddle->getX() + paddleOffset), double(paddle->getY() - paddle->getH()) };
	}
	else {
		MovingObject::update();

		SDL_Rect ballRect = getRect();
		Vector2D collVector = Vector2D(0, 0);
		if (game->collides(ballRect, speed, collVector)) { //Asks the game if there is a collision
			if(!super)
				collVector.normalize();
			speed = speed - (collVector*((speed*collVector) * 2)); //Calculate the reflection vector (R = D - 2 * (D * C) * C)
			pos = prevPos + speed; //Changes direction with the collision

			setPaddleOffset();//ineficiente
		}
	}
}

void Ball::setSpeedUp() {
	speed = { 0, -BALL_SPEED };
}

void Ball::setStuck(bool b){
	stuck = b;
}

void Ball::setPaddleOffset() {
	paddleOffset = paddle->getW() / 2 - (w / 2);
}

void Ball::setPaddleOffset(int value) {
	paddleOffset = paddle->getW() / 2 - (w / 2) - value;
}

void Ball::loadFromFile(ifstream& in) {
	MovingObject::loadFromFile(in);
	in >> stuck;
	in >> sticky;
}

void Ball::saveToFile(ofstream& out) {
	MovingObject::saveToFile(out);
	out << stuck << endl;
	out << sticky<< endl;

}
