#include "StuckReward.h"
#include "LengthenReward.h"
#include "Game.h"

void StuckReward::act() {
	game->setStickyBall(true);
}