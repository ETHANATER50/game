#include "core.h"
#include "Math\Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include <iostream>
#include <string>

//const size_t NUM_POINTS = 40;
std::vector<ew::Vector2> points = { { 0, -3 }, { 3, 4 }, { -4, 0 }, {4, 0}, {-3, 4}, {0,-3} };//{ 0, -3 }, { 3, 3 }, { 0, 1 }, { -3, 3 }, { 0, -3 }
ew::Color color{ 1,0,1 };

ew::Vector2 position{ 400.0f, 300.0f };
float scale = 4.0f;
float angle = 0.0f;

float speed = 300.0f;

float frameTime;

float roundTime = 0;

bool gameOver = false;


DWORD prevTime;
DWORD deltaTime;

ew::Shape confuser;

bool Update(float dt) { 

	frameTime = dt;

	roundTime += dt;
	if (roundTime >= 5) gameOver = true;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	if (gameOver) dt = 0;

	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	int x, y;
	Core::Input::GetMousePos(x, y);

	//ew::Vector2 target = ew::Vector2{ x, y };
	//ew::Vector2 direction = target - position;

	//if (direction.length() < 150.0f) {
	//position = position + (-direction.normalized() * speed);
	//}
	ew::Vector2 force;
	if (Core::Input::IsPressed('W')) {
		force = ew::Vector2::forward * speed;
	}
	ew::Vector2 direction = force * dt;
	direction = ew::Vector2::rotate(direction, angle);
	position += direction;


	if (position.x > 800) position.x = 0;
	if (position.x < 0) position.x = 800;
	if (position.y > 600) position.y = 0;
	if (position.y < 0) position.y = 600;

	//if (Core::Input::IsPressed('A')) position += ew::Vector2::left * (speed * dt);
	//if (Core::Input::IsPressed('D')) position += ew::Vector2::right * (speed * dt);
	//if (Core::Input::IsPressed('W')) position += ew::Vector2::up * (speed * dt);
	//if (Core::Input::IsPressed('S')) position += ew::Vector2::down * (speed * dt);

	if (Core::Input::IsPressed('A')) angle -= 3 * dt;
	if (Core::Input::IsPressed('D')) angle += 3 * dt;

	return quit; 
}
void Draw(Core::Graphics& graphics) {

	graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frameTime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime).c_str());

	if (gameOver) graphics.DrawString(400, 300, "Game Over!");

	confuser.draw(graphics, position, scale, angle);
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

	confuser.load("confuser.txt");
	confuser.setColor({ 1, 1, 1 });

	char name[] = "CSC196"; 
	Core::Init(name, 800, 600); 
	Core::RegisterUpdateFn(Update); 
	Core::RegisterDrawFn(Draw); 
	Core::GameLoop(); 
	Core::Shutdown(); }

