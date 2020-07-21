#include "Projectile.h"
#include "Math/Math.h"
#include<fstream>

bool Projectile::load(const std::string& filename) {

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

void Projectile::update(float dt) {

	ew::Vector2 direction = ew::Vector2::rotate(ew::Vector2::forward, transform.angle);
	ew::Vector2 ProjectileVelocity = direction * thrust;
	getTransform().position += ProjectileVelocity * dt;


	transform.update();

}

void Projectile::onCollision(Actor* actor) {
	if (actor->getType() == eType::ENEMY) {
		destroy = true;
	}
}
