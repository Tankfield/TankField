#include "SDL/SDL.h"

#include "Application.h"
#include "Background.h"
#include "Object.h"

int main(int argc, char* args[] ){

	Application *app = new Application();
	Background *bg = new Background(app->getScreen());
	bg->draw(0,0);
	Object obj(new Texture("tank.png", app->getScreen()));
	obj.texture->draw(0,0);
	app->Execute();
	
	return 0;
}