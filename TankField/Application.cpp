#include "Globals.h"
#include "Application.h"

Application::Application(){
	this->isRunning = this->initialize();
}

Application::~Application(){
	//Object::deleteAll();

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
	//
	SDL_WM_SetCaption("Tankfield", NULL);
	this->displaySurface = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT , 32, SDL_SWSURFACE);
	
	//TODO to remove
	weapon = new Weapon(new Texture("textures/weapon.png", displaySurface));
	weapon->missileTexture = new Texture("textures/rocket.png", displaySurface);
	//TODO to remove

			
	
	tankAnimation = new Animation("textures/tank.png", displaySurface, 4, 5, 30);
	tank = new Tank(tankAnimation, weapon);

	//TODO to remove
	bg = new Background(displaySurface);

	ter= new Terrain(displaySurface);

	gro= new Ground(displaySurface);

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
	static bool downPressed = false;
	static bool upPressed = false;

	tank->stop();
	tankAnimation->stop();
	if (this->keyState[SDLK_UP]){
		upPressed = true;
	}
	else if(upPressed)
	{
		upPressed = false;
		tank->weapon->decDegrees();
		}


	if (this->keyState[SDLK_DOWN]){
		downPressed = true;
	}
	else if(downPressed) {
		tank->weapon->incDegrees();
		downPressed = false;
	}


	if (this->keyState[SDLK_LEFT]){
		tank->moveLeft();
		tankAnimation->runBackward();
	}

	if (this->keyState[SDLK_RIGHT]){
		tank->moveRight();
		tankAnimation->runForward();
	}

	if (this->keyState[SDLK_SPACE]){
		tank->fire();
	}

}

void Application::Execute(){

	while(this->isRunning){
		this->handleEvents();
		this->handleInput();		

		
	static float lastTime = SDL_GetTicks() / 1000.0f;

	float timeSinceLastTime = (SDL_GetTicks() / 1000.0f) - lastTime;

	lastTime = SDL_GetTicks() / 1000.0f;

		Object::updateAll(timeSinceLastTime);
		
		ostringstream ostr;
		ostr << tank->weapon->getDegrees();
		SDL_WM_SetCaption(ostr.str().c_str(), NULL);

		this->render();
	}
}

void Application::render(){
	bg->draw(0,0);
	ter->draw(200,200);
	gro->draw(0,500);
	
	Object::renderAll();
	
	SDL_Flip(displaySurface);
}


