#pragma once
#include "Math/Transform.h"
#include "Graphics/Shape.h"


namespace ew {
	class Scene;

	class Actor {
	public:

		enum class eType {
			PLAYER,
			ENEMY,
			PROJECTILE	
		};


		Actor() {}
		Actor(const Transform& t, const Shape& s) { transform = t; shape = s; }

		~Actor() {}

		virtual eType getType() = 0;

		virtual bool load(const std::string& filename);
		virtual void load(std::istream& stream);

		virtual void update(float dt);
		void draw(Core::Graphics& graphics);

		virtual void onCollision(Actor* actor) {}

		bool isDestroy() { return destroy; }

		void setScene(Scene* _scene) { scene = _scene; }
		Transform& getTransform() { return transform; }
		Shape& getShape() { return shape; }

	protected:
		bool destroy{ false };
		Scene* scene{ nullptr };
		Transform transform;
		Shape shape;
	};
}