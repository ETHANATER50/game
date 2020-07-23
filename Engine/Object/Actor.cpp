#include "pch.h"
#include "Actor.h"

namespace ew {

	bool ew::Actor::load(const std::string& filename) {
		bool success = false;

		std::ifstream stream(filename);
		if (stream.is_open()) {
			success = true;

			load(stream);

			stream.close();
		}

		return success;
	}

	void Actor::load(std::istream& stream) {
		stream >> transform;

		std::string shapename;
		std::getline(stream, shapename);
		shape.load(shapename);
	}

	void ew::Actor::update(float dt) {

	}

	void ew::Actor::draw(Core::Graphics& graphics) {
		shape.draw(graphics, transform);
	}
	float Actor::getRadius()
	{
		return shape.getRadius() * transform.scale;
	}
}

