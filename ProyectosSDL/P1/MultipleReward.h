#pragma once

#include "Reward.h"

class MultipleReward : public Reward {
public:
	MultipleReward() {};
	MultipleReward(Vector2D pos, uint w, uint h, Vector2D speed, Game* g, Texture* t) :
		Reward(pos, w, h, speed, 6, g, t) {};

	~MultipleReward() {};

	void act();
};

