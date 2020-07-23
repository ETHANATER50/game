#pragma once
#include "Object\Actor.h"
class Projectile : public ew::Actor {
public:

	Projectile() {}
	virtual ~Projectile() {}

	virtual eType getType() override { return eType::PROJECTILE; }

	virtual bool load(const std::string& filename) override;
	virtual void update(float dt) override;

	virtual void onCollision(Actor* actor) override;

	void setThrust(float _speed) { thrust = _speed; };

protected:
	float thrust{ 0.0f };
	float lifetime{ 3 };
};

