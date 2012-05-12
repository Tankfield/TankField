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

	SDL_WM_SetCaption("Tankfield", NULL);
	this->displaySurface = SDL_SetVideoMode(1200, 600 , 32, SDL_SWSURFACE);
	
	//TODO to remove
	weapon = new Weapon(new Animation("textures/weapon.png", displaySurface, 1, 1, 50));

	//TODO to remove
	tank = new Tank(new Animation("textures/tank.png", displaySurface, 4, 5, 50), *weapon);

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
	tank->stop();
	if (this->keyState[SDLK_UP]){
		tank->moveUp();
		tank->texture->update();
	}

	if (this->keyState[SDLK_DOWN]){
		tank->moveDown();
		tank->texture->update();
	}

	if (this->keyState[SDLK_LEFT]){
		tank->moveLeft();
		tank->texture->update();
	}

	if (this->keyState[SDLK_RIGHT]){
		tank->moveRight();
		tank->texture->update();
	}

}

void Application::Execute(){

	while(this->isRunning){
		this->handleEvents();
		this->handleInput();		
		tank->update();
		this->render();
	}
}

void Application::render(){
	bg->drawTexture(0,0);
	tank->render();
	SDL_Flip(displaySurface);
}


