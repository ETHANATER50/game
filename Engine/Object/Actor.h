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
			PROJECTILE,
			LOCATOR
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

		float getRadius();

		bool isDestroy() { return destroy; }

		void setScene(Scene* _scene) { scene = _scene; }
		Transform& getTransform() { return transform; }
		Shape& getShape() { return shape; }

		Actor* getParent() { return parent; }
		Actor* getChild() { return child; }

		void setParent(Actor* _parent) { parent = _parent; _parent->child = this; }
		void setChild(Actor* _child) { child = _child; _child->parent = this; }

	protected:
		bool destroy{ false };
		Scene* scene{ nullptr };
		Transform transform;
		Shape shape;

		Actor* parent{ nullptr };
		Actor* child{ nullptr };
	};
}