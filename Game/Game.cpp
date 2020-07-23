#include "Game.h"
#include "Math\Math.h"
#include "Math/Random.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Object/Scene.h"
#include "Graphics/ParticleSystem.h"
#include <iostream>
#include <string>
#include <list>

namespace ew {
	void Game::initialize() {
		DWORD time = GetTickCount();
		std::cout << time / 1000 / 60 / 60 / 24 << std::endl;

		scene.startup();
		particleSystem.startup();

		Player* player = new Player;
		player->load("player.txt");
		scene.addActor(player);

		for (size_t i = 0; i < 10; i++) {

			ew::Actor* e = new Enemy;
			e->load("enemy.txt");
			dynamic_cast<Enemy*>(e)->setTarget(player);
			e->getTransform().position = { ew::random(0, 800), ew::random(0,600) };
			dynamic_cast<Enemy*>(e)->setThrust(ew::random(50, 150));
			scene.addActor(e);
		}
	}

	bool Game::update(float dt) {

		frameTime = dt;

		spawnTimer += dt;
		if (spawnTimer >= 3.0f) {
			Enemy* e = new Enemy;
			e->load("enemy.txt");
			e->setTarget(scene.getActor<Player>());
			e->getTransform().position = { ew::random(0, 800), ew::random(0,600) };
			e->setThrust(ew::random(50, 150));
			scene.addActor(e);

			spawnTimer = 0;
		}

		roundTime += dt;


		Player* player = scene.getActor<Player>();

		int x, y;
		Core::Input::GetMousePos(x, y);

		if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {
			ew::Color colors[] = { {1,1,1}, ew::Color::red, {1,1,0}, {0,1,1} };
			ew::Color color = colors[rand() % 4];
			particleSystem.create({ x,y }, 0, 180, 30, 1, color, 100, 200);

		}

		//if (Core::Input::IsPressed(VK_SPACE)) {
		//	auto enemies = scene.getActors<Enemy>();
		//	for (Enemy* enemy : enemies) {
		//		scene.removeActor(enemy);
		//	}
		//}

		bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

		DWORD time = GetTickCount();
		deltaTime = time - prevTime;
		prevTime = time;

		particleSystem.update(dt);
		scene.update(dt);

		return quit;
	}

	void Game::draw(Core::Graphics& graphics) {
		graphics.SetColor(ew::Color{ 1, 1, 0 });
		graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
		graphics.DrawString(10, 20, std::to_string(1.0f / frameTime).c_str());
		graphics.DrawString(10, 30, std::to_string(deltaTime).c_str());



		particleSystem.draw(graphics);
		scene.draw(graphics);
	}
}
