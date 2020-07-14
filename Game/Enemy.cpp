#include "Enemy.h"
#include<fstream>

bool Enemy::load(const std::string& filename) {

	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open()) {
		success = true;

		stream >> transform;

		std::string shapename;
		stream >> shapename;
		shape.load(shapename);

		stream.close();
	}

	return success;
}

void Enemy::update(float dt) {

}
