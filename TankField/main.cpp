#include "SDL/SDL.h"

#include "Application.h"
#include "Background.h"

int main(int argc, char* args[] ){

	Application *app = new Application();
	Background *bg = new Background(app->getScreen());
	bg->draw(0,0);

	app->Execute();
	
	return 0;
}