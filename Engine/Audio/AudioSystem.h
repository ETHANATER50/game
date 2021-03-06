#pragma once
#include <fmod.hpp>
#include <string>
#include <map>

namespace ew {
	class AudioSystem {
	public:
		void startup();
		void shutdown();

		void update(float dt);

		void addAudio(const std::string& name, const std::string& filename);
		void playAudio(const std::string& name, bool loop = false);

		void endLoop();

		bool isLooping();

	private:
		FMOD::System* system;
		std::map<std::string, FMOD::Sound*> sounds;
		FMOD::Channel* loopChannel{ nullptr };
	};
}

extern ew::AudioSystem audioSystem;