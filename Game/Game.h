#pragma once
#include "core.h"
#include "Object/Scene.h"

namespace ew {
	class Game {
	public:

		void initialize();

		bool update(float dt);
		void draw(Core::Graphics& graphics);

	protected:
		int score{ 0 };
		int lives{ 3 };
		float frameTime;
		float roundTime = 0;
		float spawnTimer{ 0 };

		DWORD prevTime;
		DWORD deltaTime;

		ew::Scene scene;
	};
}

