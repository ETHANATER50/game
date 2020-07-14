#pragma once
#include "Object\Actor.h"
class Enemy : public ew::Actor {

	Enemy() {}


	virtual bool load(const std::string& filename) override;
	virtual void update(float dt) override;

protected:
	float speed{ 200.0f };
};

