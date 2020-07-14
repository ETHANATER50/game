#include "core.h"
#include "Math\Math.h"
#include "Math/Random.h"
#include "Object/Actor.h"
#include "Actors/Player.h"
#include <iostream>
#include <string>

//const size_t NUM_POINTS = 40;
std::vector<ew::Vector2> points = { { 0, -3 }, { 3, 4 }, { -4, 0 }, {4, 0}, {-3, 4}, {0,-3} };//{ 0, -3 }, { 3, 3 }, { 0, 1 }, { -3, 3 }, { 0, -3 }
ew::Color color{ 1,0,1 };

float speed = 300.0f;

ew::Vector2 velocity;
float thrust = 300.0f;

float frameTime;
float roundTime = 0;
bool gameOver = false;

float t = 0;

DWORD prevTime;
DWORD deltaTime;

//ew::Shape confuser;
//ew::Transform transform{ {400, 300}, 4, 0 };

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

	//ew::Color c = ew::lerp(ew::Color{ 1, 0, 0 }, ew::Color{ 0, 1, 1 }, v);
	//graphics.SetColor(c);
	//ew::Vector2 p = ew::lerp(ew::Vector2{ 200, 200 }, ew::Vector2{ 600, 200 }, v);
	//graphics.DrawString(p.x, p.y, "Last Starfighter");

	if (gameOver) graphics.DrawString(400, 300, "Game Over!");



	//confuser.draw(graphics, transform);
	player.draw(graphics);
	enemy.draw(graphics);

	//graphics.SetColor(color);
	////graphics.DrawLine(ew::random(0.0f, 800.0f), ew::random(0.0f, 600.0f), ew::random(0.0f, 800.0f), ew::random(0.0f, 600.0f));

	//for (size_t i = 0; i < points.size() - 1; i++) {
	//	ew::Vector2 p1 = points[i];
	//	ew::Vector2 p2 = points[i + 1];

	//	p1 *= scale;
	//	p2 *= scale;

	//	p1 = ew::Vector2::rotate(p1, angle);
	//	p2 = ew::Vector2::rotate(p2, angle);


	//	p1 += position;
	//	p2 += position;

	//	graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	//}
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

