#include "Application.h"

int main(int argc, char* args[] ){

	Application *app = new Application();
	app->execute();
	delete app;
	
	return 0;
}