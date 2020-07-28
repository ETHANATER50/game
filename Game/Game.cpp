#include "Game.h"
#include "Math/Random.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Locator.h"
#include "Graphics/ParticleSystem.h"
#include <iostream>
#include <string>
#include <list>

namespace ew {
	void Game::initialize() {
		DWORD time = GetTickCount();
		std::cout << time / 1000 / 60 / 60 / 24 << std::endl;

		scene.startup();
		scene.setGame(this);


	}

	bool Game::update(float dt) {

		frameTime = dt;

		spawnTimer += dt;


		roundTime += dt;


		Player* player = scene.getActor<Player>();

		//int x, y;
		//Core::Input::GetMousePos(x, y);

		//if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {
		//	ew::Color colors[] = { {1,1,1}, ew::Color::red, {1,1,0}, {0,1,1} };
		//	ew::Color color = colors[rand() % 4];
		//	particleSystem.create({ x,y }, 0, 180, 30, 1, color, 100, 200);

		//}

		//if (Core::Input::IsPressed(VK_SPACE)) {
		//	auto enemies = scene.getActors<Enemy>();
		//	for (Enemy* enemy : enemies) {
		//		scene.removeActor(enemy);
		//	}
		//}

		bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

		switch (state) {
		case Game::State::TITLE:
			if (Core::Input::IsPressed(VK_SPACE)) {
				state = State::INIT_GAME;
			}
			break;
		case Game::State::INIT_GAME:
			lives = 3;
			state = State::START_GAME;
			break;
		case Game::State::START_GAME:
			{
				Player* player = new Player;
				player->load("player.txt");
				scene.addActor(player);
				Locator* locator = new Locator;
				locator->getTransform().position = ew::Vector2{ 0, 2 };
				player->setChild(locator);

				for (size_t i = 0; i < 10; i++) {

					ew::Actor* e = new Enemy;
					e->load("enemy.txt");
					dynamic_cast<Enemy*>(e)->setTarget(player);
					e->getTransform().position = { ew::random(0, 800), ew::random(0,600) };
					dynamic_cast<Enemy*>(e)->setThrust(ew::random(50, 150));
					scene.addActor(e);
				}
				score = 0;
				state = State::GAME;
			}

			break;
		case Game::State::GAME:
			if (spawnTimer >= 3.0f) {
				Enemy* e = new Enemy;
				e->load("enemy.txt");
				e->setTarget(scene.getActor<Player>());
				e->getTransform().position = { ew::random(0, 800), ew::random(0,600) };
				e->setThrust(ew::random(50, 150));
				scene.addActor(e);

				spawnTimer = 0;

			}
			if (score > highScore)  highScore = score; 
			break;
		case Game::State::PLAYER_DEAD:
			lives--;
			state = (lives <= 0) ? State::GAME_OVER : State::GAME_WAIT;
			stateTimer = 3;
			break;
		case Game::State::GAME_WAIT:
			stateTimer -= dt;
			if (stateTimer <= 0) {
				scene.removeAllActors();
				state = State::START_GAME;
			}
			break;
		case Game::State::GAME_OVER:
			stateTimer -= dt;
			if (stateTimer <= 0) {
				scene.shutdown();
				state = State::TITLE;
			}
			break;

		}

		DWORD time = GetTickCount();
		deltaTime = time - prevTime;
		prevTime = time;

		scene.update(dt);
		particleSystem.update(dt);


		return quit;
	}

	void Game::draw(Core::Graphics& graphics) {
		switch (state) {
		case Game::State::TITLE:
			graphics.DrawString(400, 300, "test");
			break;
		case Game::State::START_GAME:
			break;
		case Game::State::GAME:
		{
		}
			break;
		case Game::State::GAME_OVER:
			graphics.DrawString(400, 300, "GAME OVER");
			break;
		}

		graphics.SetColor(ew::Color{ 1, 1, 0 });
		std::string strScore = "SCORE: " + std::to_string(score);
		graphics.DrawString(700, 20, strScore.c_str());
		std::string livesStr = "LIVES: " + std::to_string(lives);
		graphics.DrawString(700, 30, livesStr.c_str());
		graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
		graphics.DrawString(10, 20, std::to_string(1.0f / frameTime).c_str());
		graphics.DrawString(10, 30, std::to_string(deltaTime).c_str());

		std::string strHighScore = "HIGH SCORE: " + std::to_string(highScore);
		graphics.DrawString(400, 20, strHighScore.c_str());

		scene.draw(graphics);		
		particleSystem.draw(graphics);
	}
}
