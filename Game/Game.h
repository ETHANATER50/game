#pragma once
#include "core.h"
#include "Object/Scene.h"

namespace ew {
	class Game {
	public:

		enum class State {
			TITLE,
			START_GAME,
			INIT_GAME,
			GAME,
			PLAYER_DEAD,
			GAME_WAIT,
			GAME_OVER
		};

		void initialize();

		bool update(float dt);
		void draw(Core::Graphics& graphics);

		void appPoints(int gain) { score += gain; }
		void setState(State _state) { state = _state; }

	protected:
		State state{ State::TITLE };

		int score{ 0 };
		int highScore{ 0 };
		int lives{ 3 };
		float frameTime;
		float roundTime = 0;
		float spawnTimer{ 0 };
		float stateTimer{ 0 };

		DWORD prevTime;
		DWORD deltaTime;

		ew::Scene scene;
	};
}

