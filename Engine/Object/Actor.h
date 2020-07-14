#pragma once
#include "Math/Transform.h"
#include "Graphics/Shape.h"


namespace ew {
	class Actor {
	public:
		Actor() {}
		Actor(const Transform& t, const Shape& s) { transform = t; shape = s; }

		~Actor() {}

		virtual bool load(const std::string& filename);

		virtual void update(float dt);
		void draw(Core::Graphics& graphics);

		Transform& getTransform() { return transform; }
		Shape& getShape() { return shape; }

	protected:
		Transform transform;
		Shape shape;
	};
}