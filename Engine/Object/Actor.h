#pragma once
#include "Math/Transform.h"
#include "Graphics/Shape.h"


namespace ew {
	class Actor {
	public:
		Actor() {}
		Actor(const Transform& t, const Shape& s) { transform = t; shape = s; }

		~Actor() {}

		bool load(const std::string& filename);

		void update(float dt);
		void draw(Core::Graphics& graphics);

		Transform& getTransform() { return transform; }
		Shape& getShape() { return shape; }

	private:
		Transform transform;
		Shape shape;
	};
}