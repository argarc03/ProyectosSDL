#pragma once

#include "Reward.h"

class LifeReward : public Reward {
public:
	LifeReward() {};
	LifeReward(Vector2D pos, uint w, uint h, Vector2D speed, Game* g, Texture* t) :
		Reward(pos, w, h, speed, 1, g, t) {};

	~LifeReward() {};

	void act();
};

