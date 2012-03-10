

#include <SDL\SDL.h>
#ifndef _Applicaiton_H
#define _Application_H
class Application{

private:
	
	bool isRunning;

	SDL_Event event;

	SDL_Surface *displaySurface;

	bool initialize();

	void handleEvents();

public:

	Application();
	~Application();


	void Execute();

};

#endif