#include "LaserReward.h"
#include "Game.h"
void LaserReward::act() {
	//alarga el paddle
	game->setPaddleLasers(true);
	//el tama�o del paddle se restablece cuando se pasa de nivel o se recoge otro premio!!
}
