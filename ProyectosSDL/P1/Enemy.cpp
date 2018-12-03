#include "Enemy.h"
#include "Game.h"

void Enemy::render() const {
	SDL_Rect destRect = getRect();

	texture->renderFrame(destRect, 0, frame);
}

void Enemy::update() {
	Vector2D collVector = { 0,0 };
	//Move
	if (getY() > WIN_HEIGHT - 100)
		speed = { 0, ENEMY_SPEED*(-1) };
	else if (!(game->wallCollision(getRect(), speed, collVector)) && !(game->blocksMapCollision(getRect(), speed, collVector, false))) {
		if (rand() % probability + 1 == 1) {
			speed = Vector2D(((double(rand()) / double(RAND_MAX)) * (ENEMY_SPEED - (-ENEMY_SPEED))) + (-ENEMY_SPEED),
				((double(rand()) / double(RAND_MAX)) * (ENEMY_SPEED - (-ENEMY_SPEED))) + (-ENEMY_SPEED));
		}
	}
	else
		speed = collVector;


	MovingObject::update();
	//Animation
	currentTime++;
	if (currentTime >= frameRate) {
		frame = (frame + 1) % texture->getNumCols();
		currentTime = 0;
	}


	//collision y ball direction random
	/*if (g->collidesPaddle(getRect())) { //Asks the game if there is a collision
		act();
		//g->killObject(it);//se destruye
	}
	if (pos.getY() >= WIN_HEIGHT + 2 * BALL_SIZE)//If the reward is under the paddle, it is destroyed
		;//g->killObject(it);//se destruye;*/

}

	bool Enemy::collides(const SDL_Rect& ballRect, Vector2D& collVector) {
		if (SDL_HasIntersection(&(getRect()), &ballRect)) { //Checks if there is a collision with ball
															//collVector will be a random collision vector
			int randomX = rand() % probability;
			int randomY = rand() % probability;
			collVector = { double(randomX), double(randomY) };
			collVector.normalize();
			return true;
		}

		return false;
	}

	void Enemy::setItList(list<ArkanoidObject*>::iterator _it) {
		it = _it;
	}

	void Enemy::destroy() {
		game->killObject(it);
	}

