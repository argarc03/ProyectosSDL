#include "Laser.h"
#include "Game.h"
#include <iostream>

void Laser::update() {
	MovingObject::update();//Move

	//Collision
	Vector2D aux = { 0,0 };
	if (game->blocksMapCollision(getRect(), speed, aux, true) || getY() < 4 * WALL_WIDTH) { //Asks the game if there is a collision with either the blocksMap or the topWall
		game->killObject(it);//gets destroyed
	}
}

void Laser::setItList(list<ArkanoidObject*>::iterator _it) {
	it = _it;
}