#include "Application.h"

Application::Application(){
	if(this->initialize())
		this->isRunning = true;
	else 
		this->isRunning = false;
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
	}
}