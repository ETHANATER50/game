#pragma once
#include "Object\Actor.h"
class Locator : public ew::Actor {
public:

	virtual eType getType() override { return eType::LOCATOR; }

	virtual void update(float dt) override;


};