#pragma once

#include "Reward.h"

class SuperReward : public Reward {
public:
	SuperReward() {};
	SuperReward(Vector2D pos, uint w, uint h, Vector2D speed, Game* g, Texture* t) :
		Reward(pos, w, h, speed, 5, g, t) {};

	~SuperReward() {};

	void act();
};

