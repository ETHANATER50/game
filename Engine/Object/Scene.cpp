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
