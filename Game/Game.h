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

		void addScore() { score += 100; }

	protected:
		State state{ State::TITLE };

		bool paused{ false };
		bool prevPauseButtonPressed{ false };

		int score{ 0 };
		int highScore{ 0 };
		int prevScore{ 0 };
		int lives{ 3 };
		float frameTime;
		float roundTime = 0;
		float spawnTimer{ 0 };
		float stateTimer{ 0 };

		float bombTimer{ 5 };
		int superBombs{ 3 };

		DWORD prevTime;
		DWORD deltaTime;

		ew::Scene scene;
	};
}

