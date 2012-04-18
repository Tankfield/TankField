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

	//
	memset(this->keyState, false, sizeof(this->keyState));
	
	return true;
}


void Application::handleEvents(){
	

	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_QUIT:
			this->isRunning = false;
			break;
		case SDL_KEYDOWN:
			this->keyState[event.key.keysym.sym] = true;
			
			break;
			
		case SDL_KEYUP:
			this->keyState[event.key.keysym.sym] = false;
			break;
		}
	}
}

void Application::handleInput(){
	if (this->keyState[SDLK_UP]){
		tank->moveUp();
	}

	if (this->keyState[SDLK_DOWN]){
		tank->moveDown();
	}

	if (this->keyState[SDLK_LEFT]){
		tank->moveLeft();
	}

	if (this->keyState[SDLK_RIGHT]){
		tank->moveRight();
	}

}

void Application::Execute(){

	while(this->isRunning){
		this->handleEvents();
		this->handleInput();
		this->render();
	}
}

void Application::render(){
	bg->drawTexture(0,0);
	tank->render();
	SDL_Flip(displaySurface);
}


