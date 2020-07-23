#include "Game.h"
#include "Graphics/ParticleSystem.h"



ew::Game game;


bool Update(float dt) { 
	bool quit = game.update(dt);
	return quit;
	
}
void Draw(Core::Graphics& graphics) {
	game.draw(graphics);

}
int main() { 

	char name[] = "CSC196"; 
	Core::Init(name, 800, 600); 
	game.initialize();
	Core::RegisterUpdateFn(Update); 
	Core::RegisterDrawFn(Draw); 
	Core::GameLoop(); 
	Core::Shutdown(); 
	//scene.shutdown();
	particleSystem.shutdown();
}

