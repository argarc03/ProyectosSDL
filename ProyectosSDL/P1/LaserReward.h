#pragma once
#include "Reward.h"
class LaserReward :
	public Reward
{
public:
	LaserReward() {};
	LaserReward(Vector2D pos, uint w, uint h, Vector2D speed, Game* g, Texture* t) :
		Reward(pos, w, h, speed, 7, g, t) {};

	~LaserReward() {};

	void act();
};
