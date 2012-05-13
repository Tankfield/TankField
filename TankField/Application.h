
#ifndef _Applicaiton_H
#define _Application_H
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

	Tank* tank;

	Weapon* weapon;

	bool keyState[322];

public:


	Application();
	~Application();

	void Execute();

};

#endif