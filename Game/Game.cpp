#include "core.h"
#include "Math\Math.h"
#include "Math/Random.h"
#include "Object/Actor.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include <iostream>
#include <string>
#include <list>

float speed = 300.0f;

ew::Vector2 velocity;
float thrust = 300.0f;

float frameTime;
float roundTime = 0;
bool gameOver = false;

float t = 0;

DWORD prevTime;
DWORD deltaTime;


Player player;
Enemy enemy;


std::list<Enemy*> enemies;


bool Update(float dt) { 

	frameTime = dt;

	roundTime += dt;
	//if (roundTime >= 15) gameOver = true;

	t = t + (dt * 3.0f);

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	if (gameOver) dt = 0;

	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	player.update(dt);
	enemy.update(dt);

	for (Enemy* e : enemies) {
		e->update(dt);
	}

	return quit; 
}
void Draw(Core::Graphics& graphics) {
	graphics.SetColor(ew::Color{ 1, 1, 0 });
	graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frameTime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime).c_str());

	float v = (std::sin(t) + 1.0f) * 0.5f;

	if (gameOver) graphics.DrawString(400, 300, "Game Over!");

	player.draw(graphics);
	enemy.draw(graphics);

	for (Enemy* e : enemies) {
		e->draw(graphics);
	}

}
int main() { 

	DWORD time = GetTickCount();
	std::cout << time / 1000 / 60 / 60 / 24 << std::endl;

	player.load("player.txt");
	enemy.load("enemy.txt");
	enemy.setTarget(&player);

	for (size_t i = 0; i < 10; i++) {

	Enemy* e = new Enemy;
	e->load("enemy.txt");
	e->setTarget(&player);
	e->getTransform().position = { ew::random(0, 800), ew::random(0,600) };
	e->setThrust(ew::random(50, 150));
	enemies.push_back(e);
	}


	char name[] = "CSC196"; 
	Core::Init(name, 800, 600); 
	Core::RegisterUpdateFn(Update); 
	Core::RegisterDrawFn(Draw); 
	Core::GameLoop(); 
	Core::Shutdown(); }

