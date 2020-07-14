#include "core.h"
#include "Math\Math.h"
#include "Math/Random.h"
#include "Object/Actor.h"
#include "Actors/Player.h"
#include <iostream>
#include <string>

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
ew::Actor enemy;

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

	ew::Vector2 direction = player.getTransform().position - enemy.getTransform().position;
	direction.normalize();
	ew::Vector2 enemyVelocity = direction * 150.0f;
	enemy.getTransform().position += enemyVelocity * dt;

	enemy.getTransform().angle = std::atan2(direction.y, direction.x) + ew::degreesToRadians(90);

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

}
int main() { 

	DWORD time = GetTickCount();
	std::cout << time / 1000 / 60 / 60 / 24 << std::endl;

	player.load("player.txt");
	enemy.load("enemy.txt");

	char name[] = "CSC196"; 
	Core::Init(name, 800, 600); 
	Core::RegisterUpdateFn(Update); 
	Core::RegisterDrawFn(Draw); 
	Core::GameLoop(); 
	Core::Shutdown(); }

