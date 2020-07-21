#include "Math\Math.h"
#include "Math/Random.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Object/Scene.h"
#include <iostream>
#include <string>
#include <list>


float frameTime;
float roundTime = 0;
float spawnTimer{ 0 };

float t = 0;

DWORD prevTime;
DWORD deltaTime;

ew::Scene scene;


bool Update(float dt) { 

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

	t = t + (dt * 3.0f);

	if (Core::Input::IsPressed(VK_SPACE)) {
		auto enemies = scene.getActors<Enemy>();
		for (Enemy* enemy : enemies) {
			scene.removeActor(enemy);
		}
	}

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;


	scene.update(dt);

	return quit; 
}
void Draw(Core::Graphics& graphics) {
	graphics.SetColor(ew::Color{ 1, 1, 0 });
	graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frameTime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime).c_str());

	float v = (std::sin(t) + 1.0f) * 0.5f;



	scene.draw(graphics);

}
int main() { 

	DWORD time = GetTickCount();
	std::cout << time / 1000 / 60 / 60 / 24 << std::endl;

	scene.startup();

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


	char name[] = "CSC196"; 
	Core::Init(name, 800, 600); 
	Core::RegisterUpdateFn(Update); 
	Core::RegisterDrawFn(Draw); 
	Core::GameLoop(); 
	Core::Shutdown(); 
	scene.shutdown();
}

