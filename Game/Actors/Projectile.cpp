#include "Projectile.h"
#include "Graphics/ParticleSystem.h"
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

	lifetime -= dt;
	if (lifetime <= 0) {
		destroy = true;
	}

	ew::Vector2 direction = ew::Vector2::rotate(ew::Vector2::forward, transform.angle);
	ew::Vector2 ProjectileVelocity = direction * thrust;
	getTransform().position += ProjectileVelocity * dt;

	particleSystem.create(transform.position, transform.angle + ew::PI, 20, 1, 0.5f, ew::Color{ 1, 1, 0 }, 100, 200);



	transform.update();

}

void Projectile::onCollision(Actor* actor) {
	if (actor->getType() == eType::ENEMY) {
		destroy = true;
	}
}
