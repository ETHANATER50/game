#include "pch.h"
#include "AudioSystem.h"

ew::AudioSystem audioSystem;

namespace ew {


	void ew::AudioSystem::startup() {
		FMOD::System_Create(&system);

		void* extradriverdata = nullptr;
		system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	}

	void ew::AudioSystem::shutdown() {
		for (auto& sound : sounds) {
			sound.second->release();
		}
		sounds.clear();

		system->close();
		system->release();
	}

	void ew::AudioSystem::update(float dt) {
		system->update();
	}

	void ew::AudioSystem::addAudio(const std::string& name, const std::string& filename) {
		if (sounds.find(name) == sounds.end()) {
			FMOD::Sound* sound{ nullptr };
			system->createSound( filename.c_str(), FMOD_DEFAULT, 0, &sound);
			sounds[name] = sound;
		}
	}

	void ew::AudioSystem::playAudio(const std::string& name) {
		auto iter = sounds.find(name);
		if (iter != sounds.end()) {
			FMOD::Sound* sound = iter->second;
			sound->setMode(FMOD_LOOP_OFF);
			FMOD::Channel* channel;
			system->playSound(sound, 0, false, &channel);
		}
	}
}
