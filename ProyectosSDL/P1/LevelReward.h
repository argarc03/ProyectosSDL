#pragma once

#include "Reward.h"

class LevelReward : public Reward {
public:
	LevelReward() {};
	LevelReward(Vector2D pos, uint w, uint h, Vector2D speed, Game* g, Texture* t) :
		Reward(pos, w, h, speed, 0,g, t) {};

	~LevelReward() {};

	void act();
};

