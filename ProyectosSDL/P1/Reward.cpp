#include "Reward.h"
#include "Game.h"
#include <fstream>

using namespace std;

void Reward::render() const {
	SDL_Rect destRect = getRect();

	texture->renderFrame(destRect, type, frame);
}

void Reward::setItList(list<ArkanoidObject*>::iterator itFR) {
	it = itFR;
}

void Reward::update() {
	MovingObject::update();//Move
	frame = (frame + 1) % texture->getNumCols();//Animation

	//Collision
	if (game->collidesPaddle(getRect())) { //Asks the game if there is a collision
		act();
		game->killReward(it);//se destruye
	}
	else if (pos.getY() >= WIN_HEIGHT + 2 * BALL_SIZE)//If the reward is under the paddle, it is destroyed
		game->killReward(it);//se destruye
}

void Reward::loadFromFile(ifstream& in) {
	ArkanoidObject::loadFromFile(in);
}

void Reward::saveToFile(ofstream& out) {
	out << type << endl;
	ArkanoidObject::saveToFile(out);
}