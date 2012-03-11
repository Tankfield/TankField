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
	this->displaySurface = SDL_SetVideoMode(800, 600 , 32, SDL_SWSURFACE);

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
		
		}
	}

}

void Application::Execute(){

	while(this->isRunning){
		this->handleEvents();
		this->render();
	}
}
SDL_Surface* Application::getScreen(){
		return displaySurface;
}

void Application::render(){
	SDL_Flip(displaySurface);
}