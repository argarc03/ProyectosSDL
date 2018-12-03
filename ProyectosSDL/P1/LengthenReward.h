#pragma once

#include "Reward.h"

class LengthenReward : public Reward {
public:
	LengthenReward() {};
	LengthenReward(Vector2D pos, uint w, uint h, Vector2D speed, Game* g, Texture* t) :
		Reward(pos, w, h, speed, 2,g, t) {};

	~LengthenReward() {};

	void act();
};
