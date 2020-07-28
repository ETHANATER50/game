#include "Locator.h"

void Locator::update(float dt) {

	if (parent) {
		transform.update(parent->getTransform().matrix);
	}
	else {
	transform.update();
	}
}
