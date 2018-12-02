#pragma once
class GameObject{
public:
	GameObject() {};
	virtual ~GameObject() {};

	virtual void render() const = 0;
	virtual void update() = 0;
	virtual void handleEvent() = 0;
};

