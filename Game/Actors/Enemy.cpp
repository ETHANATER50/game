#include "Enemy.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include "Object/Scene.h"
#include "../Game.h"
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
	ew::Vector2 targetPos = (target) ? target->getTransform().position : ew::Vector2{ 400, 300 };
	ew::Vector2 direction = targetPos - getTransform().position;
	direction.normalize();
	ew::Vector2 Velocity = direction * thrust;
	getTransform().position += Velocity* dt;

	getTransform().angle = std::atan2(direction.y, direction.x) + ew::degreesToRadians(90);

	transform.update();

}

void Enemy::onCollision(Actor* actor) {
	if (actor->getType() == eType::PROJECTILE) {
		destroy = true;
		audioSystem.playAudio("EnemyDeath");
		scene->getGame()->appPoints(100);

		ew::Color colors[] = { {1,1,1}, ew::Color::red, {1,1,0}, {0,1,1} };
		ew::Color color = colors[rand() % 4];
		particleSystem.create(transform.position, 0, 180, 30, 1, color, 100, 200);
	}
}

std::string Enemy::getRandomShip()
{
	int shipIndex = ew::random(0, 3);

	return ships.at(shipIndex);
}
