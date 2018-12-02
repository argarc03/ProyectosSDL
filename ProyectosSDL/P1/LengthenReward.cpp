#include "LengthenReward.h"
#include "Game.h"
void LengthenReward::act() {
	//alarga el paddle
	game->modifyPaddle(PADDLE_MODIFY_VALUE);
	//el tamaño del paddle se restablece cuando se pasa de nivel o se recoge otro premio!!
}