#include "Application.h"


Application::Application(){
	this->isRunning = this->initialize();
}

Application::~Application(){
	if(this->displaySurface != NULL) {
		SDL_FreeSurface(displaySurface);
	}

	SDL_Quit();
}

bool Application::initialize(){
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		this->displaySurface = NULL;
		return false;
	}

	SDL_WM_SetCaption("TANKFIELD", NULL);
	this->displaySurface = SDL_SetVideoMode(1200, 600 , 32, SDL_SWSURFACE);
	

	//TODO to remove
	tank = new Object(new Texture("tank.png", displaySurface));

	//TODO to remove
	bg = new Background(displaySurface);

	if(this->displaySurface == NULL){
		return false;
	}

	return true;
}


void Application::handleEvents(){
	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_QUIT:
			this->isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_LEFT){
				tank->moveLeft();
			}
			if (event.key.keysym.sym == SDLK_RIGHT){
				tank->moveRight();
			}
			break;
		
		}
	}

}

void Application::Execute(){

	while(this->isRunning){
		this->handleEvents();
		this->render();
	}
}

void Application::render(){
	bg->drawTexture(0,0);
	tank->render();
	SDL_Flip(displaySurface);
}