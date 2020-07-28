#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Graphics/ParticleSystem.h"
#include "Math/Math.h" 
#include "Math/Random.h"
#include "Object/Scene.h"
#include "..//Game.h"
#include <fstream>

bool Player::load(const std::string& filename) {

	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open()) {
		success = true;

		Actor::load(stream);

		stream >> thrust;
		stream >> yawRate;

		stream.close();
	}

	return success;
}

void Player::update(float dt) {
	fireTimer += dt;

	if (Core::Input::IsPressed(VK_SPACE)&& fireTimer >= fireRate) {
		Projectile* e = new Projectile;
		e->load("projectile.txt");
		e->getTransform().position = transform.position;
		e->getTransform().angle = transform.angle;
		scene->addActor(e);
		fireTimer = 0;
	}

	ew::Vector2 force;
	if (Core::Input::IsPressed('W')) {
		force = ew::Vector2::forward * thrust;
	}
	ew::Vector2 direction = force * dt;
	force = ew::Vector2::rotate(force, transform.angle);

	velocity = velocity + (force * dt);
	velocity *= 0.98f;
	transform.position += velocity * dt;

	if (transform.position.x > 800) transform.position.x = 0;
	if (transform.position.x < 0)  transform.position.x = 800;
	if (transform.position.y > 600) transform.position.y = 0;
	if (transform.position.y < 0) transform.position.y = 600;

	if (Core::Input::IsPressed('A')) transform.angle -= dt * ew::degreesToRadians(yawRate);
	if (Core::Input::IsPressed('D')) transform.angle += dt * ew::degreesToRadians(yawRate);

	if (force.lengthSqr() > 0) {
		ew::Vector2 childPosition = child->getTransform().matrix.getPosition();

		particleSystem.create(childPosition, transform.angle + ew::PI, 20, 1, 0.5f, ew::Color{ 1, 1, 0 }, 100, 200);
	}

	if (Core::Input::IsPressed('E') && !prevButtonPress) {
		transform.position = ew::Vector2{ ew::random(0, 800), ew::random(0, 600) };
		transform.angle =  ew::random(0, ew::TWO_PI);
	}

	prevButtonPress = Core::Input::IsPressed('E');

	transform.update();

	if (child) {
		child->update(dt);
	}
}

void Player::onCollision(Actor* actor) {
	if (!destroy && actor->getType() == eType::ENEMY) {
		destroy = true;
		scene->getGame()->setState(ew::Game::State::PLAYER_DEAD);

		auto enemies = scene->getActors<Enemy>();
		for (auto enemy : enemies) {
			enemy->setTarget(nullptr);
		}

		ew::Color colors[] = { {1,1,1}, ew::Color::red, {1,1,0}, {0,1,1} };
		ew::Color color = colors[rand() % 4];
		particleSystem.create(transform.position, 0, 180, 100, 2, color, 100, 200);
	}
}
