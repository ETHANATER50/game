#pragma once
#include "Object/Actor.h"

class Player : public ew::Actor {

public:
	Player() {}
	virtual ~Player() {}

	virtual bool load(const std::string& filename) override;
	virtual void update(float dt) override;

protected:
	float thrust{ 200.0f };
	ew::Vector2 velocity;
	float yawRate;
};