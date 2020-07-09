#include "core.h"
#include "Math\Math.h"
#include "Math/Random.h"
#include "Object/Actor.h"
#include <iostream>
#include <string>

//const size_t NUM_POINTS = 40;
std::vector<ew::Vector2> points = { { 0, -3 }, { 3, 4 }, { -4, 0 }, {4, 0}, {-3, 4}, {0,-3} };//{ 0, -3 }, { 3, 3 }, { 0, 1 }, { -3, 3 }, { 0, -3 }
ew::Color color{ 1,0,1 };



float speed = 300.0f;

float frameTime;
float roundTime = 0;
bool gameOver = false;


DWORD prevTime;
DWORD deltaTime;

ew::Shape confuser;
ew::Transform transform{ {400, 300}, 4, 0 };

bool Update(float dt) { 

	frameTime = dt;

	roundTime += dt;
	if (roundTime >= 15) gameOver = true;

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
	direction = ew::Vector2::rotate(direction, transform.angle);
	transform.position += direction;

	//transform.position = ew::clamp(transform.position, ew::Vector2{ 0,0 }, ew::Vector2{ 800, 600 });

	transform.position.x = ew::clamp(transform.position.x, 0.0f, 800.0f);
	transform.position.y = ew::clamp(transform.position.y, 0.0f, 600.0f);

	//if (transform.position.x > 800) transform.position.x = 0;
	//if (transform.position.x < 0) transform.position.x = 800;
	//if (transform.position.y > 600) transform.position.y = 0;
	//if (transform.position.y < 0) transform.position.y = 600;

	//if (Core::Input::IsPressed('A')) position += ew::Vector2::left * (speed * dt);
	//if (Core::Input::IsPressed('D')) position += ew::Vector2::right * (speed * dt);
	//if (Core::Input::IsPressed('W')) position += ew::Vector2::up * (speed * dt);
	//if (Core::Input::IsPressed('S')) position += ew::Vector2::down * (speed * dt);

	if (Core::Input::IsPressed('A')) transform.angle -= dt * ew::degreesToRadians(360.0f);
	if (Core::Input::IsPressed('D')) transform.angle += dt * ew::degreesToRadians(360.0f);

	return quit; 
}
void Draw(Core::Graphics& graphics) {
	graphics.SetColor(ew::Color{ 1, 1, 0 });
	graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frameTime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime).c_str());

	if (gameOver) graphics.DrawString(400, 300, "Game Over!");

	confuser.draw(graphics, transform);
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

	char name[] = "CSC196"; 
	Core::Init(name, 800, 600); 
	Core::RegisterUpdateFn(Update); 
	Core::RegisterDrawFn(Draw); 
	Core::GameLoop(); 
	Core::Shutdown(); }

