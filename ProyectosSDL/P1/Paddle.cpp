#include "Paddle.h"
#include "Game.h"

//If the paddle is inside the limits, the paddle moves.
void Paddle::update() {
	if (inside())
		pos = pos + speed;
	laserTimer++;
	if (lasers) {
		if(laserTimer % LASER_DELAY == 0)
			game->createLasers();
			//lasers = false;
	}
}

bool Paddle::inside() {
	return (speed.getX() < 0 && getX() > WALL_WIDTH + 3 * GAP_WIDTH) ||
		(speed.getX() >= 0 && getX() + getW() < WIN_WIDTH - WALL_WIDTH - 3 * GAP_WIDTH);
}

void Paddle::handleEvents(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_LEFT) {
			movingRight = false;
			movingLeft = true;

			speed = Vector2D(-PADDLE_SPEED, 0);
		}
		else if (event.key.keysym.sym == SDLK_RIGHT) {
			movingRight = true;
			movingLeft = false;

			speed = Vector2D(PADDLE_SPEED, 0);
		}
		else if (event.key.keysym.sym == SDLK_SPACE) {
			game->setStuckBall(false);
		}
	}
	else if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == SDLK_LEFT) {
			if (movingLeft)
				speed = Vector2D(0, 0);
		}
		else if (event.key.keysym.sym == SDLK_RIGHT) {
			if (movingRight)
				speed = Vector2D(0, 0);
		}
	}
}

bool Paddle::collides(const SDL_Rect& ballRect, Vector2D& collVector) {
	Vector2D p2 = { double(ballRect.x),  double(ballRect.y) + double(ballRect.h) }; // bottom-left
	Vector2D p3 = { double(ballRect.x) + double(ballRect.w),  double(ballRect.y) + double(ballRect.h) }; // bottom-right

	//Checks that the ball is hitting the top of the paddle.
	if (getY() <= p2.getY() && getY() + getH() > p2.getY() && getX() <= p3.getX() && getX() + getW() >= p2.getX()) {
		double paddleCenter = getX() + getW() / 2;
		double ballCenter = p2.getX() + double(ballRect.w) / 2;
		double distance = paddleCenter - ballCenter;

		//Compare the distance between the center of the ball and the paddle.
		if (distance < 0)
			collVector = { REFLECTION,-1 };//Right
		else if (distance > 0)
			collVector = { -REFLECTION,-1 };//Left
		else
			collVector = { 0,-1 };//Center
		return true;
	}
	return false;
} 

void Paddle::modifyWidth(int value) {

	if ((w > PADDLE_WIDTH && value < 0) || (w < PADDLE_WIDTH && value > 0) || w == PADDLE_WIDTH)
	{
		w += value;

		//Centers the paddle after modifying its width
		pos = pos - Vector2D(value / 2, 0);

		//RECALCULAR EL OFFSET
	}
}

