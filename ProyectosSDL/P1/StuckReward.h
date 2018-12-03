#pragma once
#include "Reward.h"
class StuckReward :
	public Reward
{
public:
	StuckReward() {};
	StuckReward(Vector2D pos, uint w, uint h, Vector2D speed, Game* g, Texture* t) :
		Reward(pos, w, h, speed, 4, g, t) {};

	~StuckReward() {};

	void act();
};

