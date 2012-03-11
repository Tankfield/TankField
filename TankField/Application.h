
#ifndef _Applicaiton_H
#define _Application_H
#include <SDL\SDL.h>

class Application{

private:
	
	bool isRunning;

	SDL_Event event;

	SDL_Surface *displaySurface;

	bool initialize();

	void handleEvents();

	void render();

public:


	Application();
	~Application();

	void Execute();

	SDL_Surface* getScreen();

};

#endif