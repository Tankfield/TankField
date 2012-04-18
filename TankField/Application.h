
#ifndef _Applicaiton_H
#define _Application_H
#include <SDL\SDL.h>
#include "Object.h"
#include "Background.h"

class Application{

private:
	
	Background* bg;

	bool isRunning;

	SDL_Event event;

	SDL_Surface *displaySurface;

	bool initialize();

	void handleEvents();

	void handleInput();

	void render();

	Object* tank;

	bool keyState[322];

public:


	Application();
	~Application();

	void Execute();

};

#endif