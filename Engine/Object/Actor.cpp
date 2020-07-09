#include "pch.h"
#include "Actor.h"

namespace ew {

	bool ew::Actor::load(const std::string& filename) {
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

	void ew::Actor::update(float dt) {

	}

	void ew::Actor::draw(Core::Graphics& graphics) {
		shape.draw(graphics, transform);
	}
}

