#include "Wall.h"
#include "Game.h"

//Returns true if collides with a wall and returns the collVector
bool Wall::collides(const SDL_Rect& ballRect, const Vector2D& ballVel, Vector2D& collVector) {
	SDL_Rect rect = getRect();
	if (SDL_HasIntersection(&ballRect, &rect)) {
		collVector = collision;
		return true;
	}

	return false;
}
