
#ifndef _Applicaiton_H
#define _Application_H
#include <sstream>
using std::ostringstream;

#include <SDL\SDL.h>
#include "Object.h"
#include "Background.h"
#include "Animation.h"
#include "Tank.h"
#include "Weapon.h"
#include "Vector2D.h"
#include "Terrain.h"
#include "Ground.h"
#include "Missile.h"
#include "Player.h"

class Application{

private:
	
	Background* bg;
	Terrain* ter;
	Ground* gro;

	bool isRunning;

	SDL_Event event;

	SDL_Surface *displaySurface;

	bool initialize();
	void handleEvents();
	void handleInput();
	void render();

	Tank *tank1;
	Tank *tank2;
	Player *player1;
	Player *player2;
	Animation *tankAnimation1;
	Animation *tankAnimation2;
	Animation *weaponAnimation1;
	Animation *weaponAnimation2;
	Weapon* weapon1;
	Weapon* weapon2;

	bool keyState[322];

public:


	Application();
	~Application();

	void Execute();

};

#endif