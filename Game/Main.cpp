#include "Game.h"
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include <time.h>



ew::Game game;


bool Update(float dt) { 
	bool quit = game.update(dt);
	return quit;
	
}
void Draw(Core::Graphics& graphics) {
	game.draw(graphics);

}
int main() { 

	//srand(time(NULL));

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	audioSystem.startup();
	game.initialize();
	particleSystem.startup();
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
	Core::Shutdown();
	//scene.shutdown();
	particleSystem.shutdown();
	audioSystem.shutdown();
}

