#include "LifeReward.h"
#include "Game.h"

void LifeReward::act() {
	game->lifeUp();//otorga una vida extra
}
