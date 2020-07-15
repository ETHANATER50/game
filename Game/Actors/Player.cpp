#include "Player.h"
#include "Math/Math.h" 
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
	ew::Vector2 force;
	if (Core::Input::IsPressed('W')) {
		force = ew::Vector2::forward * thrust;
	}
	ew::Vector2 direction = force * dt;
	force = ew::Vector2::rotate(force, transform.angle);

	velocity = velocity + (force * dt);
	velocity *= 0.98;
	transform.position += velocity * dt;

	if (transform.position.x > 800) transform.position.x = 0;
	if (transform.position.x < 0)  transform.position.x = 800;
	if (transform.position.y > 600) transform.position.y = 0;
	if (transform.position.y < 0) transform.position.y = 600;

	if (Core::Input::IsPressed('A')) transform.angle -= dt * ew::degreesToRadians(yawRate);
	if (Core::Input::IsPressed('D')) transform.angle += dt * ew::degreesToRadians(yawRate);

	transform.update();
}
