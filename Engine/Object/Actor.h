#pragma once
#include "Math/Transform.h"
#include "Graphics/Shape.h"


namespace ew {
	class Scene;

	class Actor {
	public:
		Actor() {}
		Actor(const Transform& t, const Shape& s) { transform = t; shape = s; }

		~Actor() {}

		virtual bool load(const std::string& filename);
		virtual void load(std::istream& stream);

		virtual void update(float dt);
		void draw(Core::Graphics& graphics);


		void setScene(Scene* _scene) { scene = _scene; }
		Transform& getTransform() { return transform; }
		Shape& getShape() { return shape; }

	protected:
		Scene* scene{ nullptr };
		Transform transform;
		Shape shape;
	};
}