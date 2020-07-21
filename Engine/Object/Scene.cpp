#include "pch.h"
#include "Scene.h"

void ew::Scene::startup() {

}

void ew::Scene::shutdown() {
	for (Actor* a : actors) {
		delete a;
	}
	actors.clear();
}

void ew::Scene::update(float dt) {

	std::vector<Actor*> _actors{ actors.begin(), actors.end() };
	for (size_t i = 0; i < _actors.size(); i++) {

		for (size_t j = i + 1; j < _actors.size(); j++) {

			float distance = ew::Vector2::distance(_actors[i]->getTransform().position, _actors[j]->getTransform().position);
			if (distance <= 10) {
				_actors[i]->onCollision(_actors[j]);
				_actors[j]->onCollision(_actors[i]);
			}
		}

	}

	auto iter = actors.begin();
	while (iter != actors.end()) {
		if ((*iter)->isDestroy()) {
			delete(*iter);
			iter = actors.erase(iter);
		}
		else {
			iter++;
		}
	}

	for (Actor* a : actors) {
		a->update(dt);
	}
}

void ew::Scene::draw(Core::Graphics& graphics) {
	for (Actor* a : actors) {
		a->draw(graphics);
	}
}

void ew::Scene::addActor(Actor* actor) {
	actor->setScene(this);
	actors.push_back(actor);
}

void ew::Scene::removeActor(Actor* object) {
	std::list<Actor*>::iterator iter = std::find(actors.begin(), actors.end(), object); if (iter != actors.end()) {
		if (iter != actors.end()) {
			delete* iter;
			actors.erase(iter);
		}
	}
}
