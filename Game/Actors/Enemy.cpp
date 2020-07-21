#include "Enemy.h"
#include "Math/Math.h"
#include<fstream>

bool Enemy::load(const std::string& filename) {

	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open()) {
		success = true;

		Actor::load(stream);

		stream >> thrust;

		stream.close();
	}

	return success;
}

void Enemy::update(float dt) {

	ew::Vector2 direction = target->getTransform().position - getTransform().position;
	direction.normalize();
	ew::Vector2 Velocity = direction * thrust;
	getTransform().position += 0;// Velocity* dt;

	getTransform().angle = std::atan2(direction.y, direction.x) + ew::degreesToRadians(90);

	transform.update();

}

void Enemy::onCollision(Actor* actor) {
	if (actor->getType() == eType::PROJECTILE) {
		destroy = true;
	}
}
