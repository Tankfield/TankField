#include "SDL/SDL.h"

#include "Application.h"

int main(int argc, char* args[] ){

	Application *app = new Application();

	app->Execute();

	delete app;

	return 0;
}