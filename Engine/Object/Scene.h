#pragma once
#include "core.h"
#include "Actor.h"
#include <vector>
#include <list>


namespace ew {
	class Scene {
	public:
		void startup();
		void shutdown();

		void update(float dt);
		void draw(Core::Graphics& graphics);

		void addActor(class Actor* actor);
		void removeActor(class Actor* object);

		template <typename T>
		T* getActor() {
			T* actor{ nullptr };

			for (ew::Actor* a : actors) {
				actor = dynamic_cast<T*>(a);
				if (actor) break;
			}

			return actor;
		}

		template <typename T>
		std::vector<T*> getActors() {
			std::vector<T*> foundActors;

			for (ew::Actor* a : actors) {
				T* actor = dynamic_cast<T*>(a);
				if (actor) {
					foundActors.push_back(actor);
				}
			}

			return foundActors;
		}

	private:
		std::list<class Actor*> actors;
	};
}