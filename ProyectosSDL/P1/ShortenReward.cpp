#include "ShortenReward.h"
#include "Game.h"

void ShortenReward::act() {
	//acorta el paddle
	game->modifyPaddle(-PADDLE_MODIFY_VALUE);

	//el tama�o del paddle se restablece cuando se pasa de nivel o se recoge otro premio!!
}