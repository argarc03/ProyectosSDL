#pragma once

#include "Reward.h"

class ShortenReward : public Reward {
public:
	ShortenReward() {};
	ShortenReward(Vector2D pos, uint w, uint h, Vector2D speed, Game* g, Texture* t) :
		Reward(pos, w, h, speed, 3,g, t) {};

	~ShortenReward() {};

	void act();
};

