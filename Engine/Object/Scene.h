#pragma once
#include "core.h"
#include "Actor.h"
#include <vector>
#include <list>



namespace ew {
	class Game;
	class Scene {
	public:
		void startup();
		void shutdown();

		void update(float dt);
		void draw(Core::Graphics& graphics);

		void addActor(class Actor* actor);
		void removeActor(class Actor* object);
		void removeAllActors() {
			for (Actor* a : actors) {
				delete a;
			}
			actors.clear();
		}

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

		void setGame(Game* _game) { game = _game; }
		Game* getGame() { return game; }

	private:
		Game* game;
		std::list<class Actor*> actors;
	};
}