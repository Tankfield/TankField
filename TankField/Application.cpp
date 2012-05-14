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
	SDL_WM_SetCaption("Tankfield", NULL);
	this->displaySurface = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT , 32, SDL_SWSURFACE);
	
	//TODO to remove
	weaponAnimation1 = new Animation("textures/weapon.png", displaySurface, 3, 5, 15);
	weapon1 = new Weapon(weaponAnimation1);
	weaponAnimation2 = new Animation("textures/redweapon.png", displaySurface, 3, 5, 15);
	weapon2 = new Weapon(weaponAnimation2);

	weapon1->missileTexture = new Texture("textures/missile.png", displaySurface);
	weapon2->missileTexture = new Texture("textures/missile.png", displaySurface);
	//TODO to remove

			
	
	tankAnimation1 = new Animation("textures/grtank.png", displaySurface, 4, 5, 30);
	tank1 = new Tank(tankAnimation1, weapon1);
	tankAnimation2 = new Animation("textures/redtank.png", displaySurface, 4, 5, 30);
	tank2 = new Tank(tankAnimation2, weapon2);

	player1 = new Player(tank1, tankAnimation1, weaponAnimation1);
	player2 = new Player(tank2, tankAnimation2, weaponAnimation2);
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
	static bool wPressed = false;
	static bool sPressed = false;

	//To add player->stop()
	//player1->tank->stop();
	//player1->tankAnimation->stop();
	//player1->weaponAnimation->stop();
	player1->stop();
	//player2->tank->stop();
	//player2->tankAnimation->stop();
	//player2->weaponAnimation->stop();
	player2->stop();

	if (this->keyState[SDLK_UP]){
		upPressed = true;
	}
	else if(upPressed){
		if(player1->tank->weapon->getDegrees() > -65){
			player1->tank->weapon->decDegrees();
			player1->weaponAnimation->runForward();
		}
		upPressed = false;
	}


	if (this->keyState[SDLK_DOWN]){
		downPressed = true;
	}
	else if(downPressed) {
		if(player1->tank->weapon->getDegrees() < 75){
			player1->tank->weapon->incDegrees();
			player1->weaponAnimation->runBackward();
		}
		downPressed = false;
	}


	if (this->keyState[SDLK_LEFT]){
		player1->tank->moveLeft();
		player1->tankAnimation->runBackward();
	}

	if (this->keyState[SDLK_RIGHT]){
		player1->tank->moveRight();
		player1->tankAnimation->runForward();
	}

	if (this->keyState[SDLK_SPACE]){
		tank1->fire();
	}

	//////////////////////

	if (this->keyState[SDLK_w]){
		wPressed = true;
	}
	else if(wPressed){
		if(player2->tank->weapon->getDegrees() > -65){
			player2->tank->weapon->decDegrees();
			player2->weaponAnimation->runForward();
		}
		wPressed = false;
	}


	if (this->keyState[SDLK_s]){
		sPressed = true;
	}
	else if(sPressed) {
		if(player2->tank->weapon->getDegrees() < 75){
			player2->tank->weapon->incDegrees();
			player2->weaponAnimation->runBackward();
		}
		sPressed = false;
	}


	if (this->keyState[SDLK_a]){
		player2->tank->moveLeft();
		player2->tankAnimation->runBackward();
	}

	if (this->keyState[SDLK_d]){
		player2->tank->moveRight();
		player2->tankAnimation->runForward();
	}

	if (this->keyState[SDLK_SPACE]){
		tank2->fire();
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
		ostr << player1->tank->weapon->getDegrees() << " " << player2->tank->weapon->getDegrees();
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


