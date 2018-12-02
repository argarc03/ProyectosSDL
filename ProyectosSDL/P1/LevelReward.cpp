#include "LevelReward.h"
#include "Game.h"

void LevelReward::act() {
	game->toggleLevelWin();//pasa de nivel
}
