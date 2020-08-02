#include "Game.h"
#include "Math/Random.h"
#include "Math/Math.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Locator.h"
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>

namespace ew {
	void Game::initialize() {
		DWORD time = GetTickCount();
		std::cout << time / 1000 / 60 / 60 / 24 << std::endl;

		scene.startup();
		scene.setGame(this);

		audioSystem.addAudio("Shoot", "shoot.wav");
		audioSystem.addAudio("PlayerDeath", "PlayerDeath.wav");
		audioSystem.addAudio("EnemyDeath", "EnemyDeath.wav");
		audioSystem.addAudio("Alert", "alert.wav");
		audioSystem.addAudio("MenuMusic", "MenuMusic.wav");
		audioSystem.addAudio("GameMusic", "GameMusic.wav");
		audioSystem.addAudio("SuperBomb", "superBomb.wav");
		audioSystem.addAudio("Warp", "Warp.wav");

		std::ifstream stream;
		stream.open("highScore.txt");
			if (stream.is_open()) {

				stream >> highScore;


				stream.close();
			}

	}

	bool Game::update(float dt) {

		if (paused) dt = 0;
		
		bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

		frameTime = dt;

		spawnTimer += dt;
		roundTime += dt;
		bombTimer += dt;


		Player* player = scene.getActor<Player>();

		//int x, y;
		//Core::Input::GetMousePos(x, y);

		//if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {
		//	ew::Color colors[] = { {1,1,1}, ew::Color::red, {1,1,0}, {0,1,1} };
		//	ew::Color color = colors[rand() % 4];
		//	particleSystem.create({ x,y }, 0, 180, 30, 1, color, 100, 200);

		//}


		//}



		switch (state) {
		case Game::State::TITLE:
			if (Core::Input::IsPressed(VK_SPACE)) {
				state = State::INIT_GAME;
			}
			if (!(audioSystem.isLooping())) {
			audioSystem.playAudio("MenuMusic", true);
			}
			break;
		case Game::State::INIT_GAME:
			lives = 3;
			score = 0;
			superBombs = 3;
			state = State::START_GAME;
			break;
		case Game::State::START_GAME:
			{
				dt = 0;
				Player* player = new Player;
				player->load("player.txt");
				scene.addActor(player);

				Locator* locator = new Locator;
				locator->getTransform().position = ew::Vector2{ 4, 2 };
				player->addChild(locator);
				locator = new Locator;
				locator->getTransform().position = ew::Vector2{ -4, 2 };
				player->addChild(locator);

				for (size_t i = 0; i < 7; i++) {

					ew::Actor* e = new Enemy;
					e->load(dynamic_cast<Enemy*>(e)->getRandomShip());
					dynamic_cast<Enemy*>(e)->setTarget(scene.getActor<Player>());
					float distance = ew::random(200, 400);
					float angle = ew::random(0, ew::TWO_PI);
					ew::Vector2 position = ew::Vector2::rotate({ 0.0f, distance }, angle);

					e->getTransform().position = scene.getActor<Player>()->getTransform().position + position;//{ ew::random(0, 800), ew::random(0,600) };
					dynamic_cast<Enemy*>(e)->setThrust(ew::random(60, 100));
					scene.addActor(e);
				}
				audioSystem.endLoop();
				audioSystem.playAudio("GameMusic", true);
				spawnTimer = 0;
				state = State::GAME;
			}

			break;
		case Game::State::GAME:
			if (spawnTimer >= 6.0f) {
				for (size_t i = 0; i < 5; i++) {

					ew::Actor* e = new Enemy;
					e->load(dynamic_cast<Enemy*>(e)->getRandomShip());
					dynamic_cast<Enemy*>(e)->setTarget(scene.getActor<Player>());
					float distance = ew::random(200, 400);
					float angle = ew::random(0, ew::TWO_PI);
					ew::Vector2 position = ew::Vector2::rotate({ 0.0f, distance }, angle);

					e->getTransform().position = scene.getActor<Player>()->getTransform().position + position;//{ ew::random(0, 800), ew::random(0,600) };
					dynamic_cast<Enemy*>(e)->setThrust(ew::random(60, 100));
					scene.addActor(e);
				}
				audioSystem.playAudio("Alert");
				spawnTimer = 0;

			}
			if (score > highScore) {
				highScore = score;
				std::ofstream stream("highScore.txt", std::ofstream::trunc);
				stream << highScore;
			}
			if (score != 0 && score % 3000 == 0 && prevScore % 3000 != 0) lives++;
			prevScore = score;

			if (Core::Input::IsPressed('Q') && superBombs > 0 && bombTimer >= 5) {
				auto enemies = scene.getActors<Enemy>();
				for (Enemy* enemy : enemies) {
					scene.removeActor(enemy);
					score += 100;
					if (score % 3000 == 0) lives++;

				}
				audioSystem.playAudio("SuperBomb");
				bombTimer = 0;
				superBombs--;
			}

			if (Core::Input::IsPressed('P') && !prevPauseButtonPressed) paused = !paused;
			prevPauseButtonPressed = Core::Input::IsPressed('P');
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

		if(!paused) scene.update(dt);
		particleSystem.update(dt);
		audioSystem.update(dt);


		return quit;
	}

	void Game::draw(Core::Graphics& graphics) {
		switch (state) {
		case Game::State::TITLE:
			graphics.SetColor(Color{ 1, 1, 0 });
			graphics.DrawString(400, 300, "The Mandalorian");
			break;
		case Game::State::START_GAME:
			break;
		case Game::State::GAME:
		{
			graphics.SetColor(Color{ 1, 1, 0 });
			std::string strScore = "SCORE: " + std::to_string(score);
			graphics.DrawString(700, 20, strScore.c_str());
			std::string livesStr = "LIVES: " + std::to_string(lives);
			graphics.DrawString(700, 35, livesStr.c_str());
			std::string bombsStr = "BOMBS (Q): " + std::to_string(superBombs);
			graphics.DrawString(700, 50, bombsStr.c_str());
			std::string strHighScore = "HIGH SCORE: " + std::to_string(highScore);
			graphics.DrawString(400, 20, strHighScore.c_str());
		}
			break;
		case Game::State::GAME_OVER:
			graphics.DrawString(400, 300, "GAME OVER");
			break;
		}

		//graphics.SetColor(Color{ 1, 1, 0 });
		//graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
		//graphics.DrawString(10, 20, std::to_string(1.0f / frameTime).c_str());
		//graphics.DrawString(10, 30, std::to_string(deltaTime).c_str());

		if (paused) {
			graphics.DrawString(380, 300, "Paused");

		}

		scene.draw(graphics);		
		particleSystem.draw(graphics);
	}
}
