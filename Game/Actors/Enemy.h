#pragma once
#include "Object\Actor.h"
class Enemy : public ew::Actor {
public:

	Enemy() {}
	virtual ~Enemy() {}

	virtual eType getType() override { return eType::ENEMY; }

	virtual bool load(const std::string& filename) override;
	virtual void update(float dt) override;

	virtual void onCollision(Actor* actor) override;

	void setTarget(Actor* actor) { target = actor; }
	void setThrust(float _speed) { thrust = _speed; };

protected:
	float thrust{ 0.0f };
	Actor* target{ nullptr };
};

