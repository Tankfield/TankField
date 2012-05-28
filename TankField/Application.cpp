#include "Globals.h"
#include "Application.h"

Application::Application(){
	this->isRunning = this->initialize();
}

Application::~Application(){
	Object::deleteAll();

	if(this->displaySurface != NULL) {
		SDL_FreeSurface(displaySurface);
	}

	SDL_Quit();
}

void Application::loadContent(){
	background = new Background(displaySurface);
	terrain = new Terrain(displaySurface);
	ground = new Ground(displaySurface);
	weaponAnimation1 = new Animation("textures/weapon.png", displaySurface, 3, 5, 15);
	weapon1 = new Weapon(weaponAnimation1, TANK1_WEAPON_DEGREES);
	weaponAnimation2 = new Animation("textures/redweapon.png", displaySurface, 3, 5, 15);
	weapon2 = new Weapon(weaponAnimation2, TANK2_WEAPON_DEGREES);
	weapon1->missileTexture = new Texture("textures/missile.png", displaySurface);
	weapon2->missileTexture = new Texture("textures/missile.png", displaySurface);
	tankAnimation1 = new Animation("textures/grtank.png", displaySurface, 4, 5, 30);
	tank1 = new Tank(tankAnimation1, weapon1, Vector2D(TANK1_POS_Y,TANK1_POS_X), Vector2D(TANK1_WEAPON_POS_X,TANK1_WEAPON_POS_Y));
	tankAnimation2 = new Animation("textures/redtank.png", displaySurface, 4, 5, 30);
	tank2 = new Tank(tankAnimation2, weapon2, Vector2D(TANK2_POS_Y,TANK2_POS_X), Vector2D(TANK2_WEAPON_POS_X,TANK2_WEAPON_POS_Y));
	player1 = new Player(tank1, tankAnimation1, weaponAnimation1);
	player2 = new Player(tank2, tankAnimation2, weaponAnimation2);	
}

bool Application::initialize(){
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		this->displaySurface = NULL;
		return false;
	}
	SDL_WM_SetCaption("Tankfield", NULL);
	this->displaySurface = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT , 32, SDL_SWSURFACE);

	loadContent();

	if(this->displaySurface == NULL){
		return false;
	}
	memset(this->keyState, false, sizeof(this->keyState));
	srand(time(NULL));

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


	player1->stop();
	player2->stop();

	//player1 controls
	if (this->keyState[SDLK_w]){
		wPressed = true;
	}
	else if(wPressed){
		if(player1->tank->weapon->getDegrees() > -65){
			player1->tank->weapon->decDegrees();
			player1->weaponAnimation->runForward();
		}
		wPressed = false;
	}


	if (this->keyState[SDLK_s]){
		sPressed = true;
	}
	else if(sPressed) {
		if(player1->tank->weapon->getDegrees() < 75){
			player1->tank->weapon->incDegrees();
			player1->weaponAnimation->runBackward();
		}
		sPressed = false;
	}


	if (this->keyState[SDLK_a]){
		if(!player1->tank->outOfScreen()){
			player1->tank->moveLeft();
			player1->tankAnimation->runBackward();
		}
	}

	if (this->keyState[SDLK_d]){
		player1->tank->moveRight();
		player1->tankAnimation->runForward();
	}

	if (this->keyState[SDLK_SPACE]){
		tank1->fire();
	}

	//player2 controls

	if (this->keyState[SDLK_DOWN]){
		downPressed = true;
	}
	else if(downPressed){
		if(player2->tank->weapon->getDegrees() > -75){
			player2->tank->weapon->decDegrees();
			player2->weaponAnimation->runBackward();
		}
		downPressed = false;
	}


	if (this->keyState[SDLK_UP]){
		upPressed = true;
	}
	else if(upPressed){
		if(player2->tank->weapon->getDegrees() < 65){
			player2->tank->weapon->incDegrees();
			player2->weaponAnimation->runForward();
		}
		upPressed = false;
	}


	if (this->keyState[SDLK_LEFT]){
		player2->tank->moveLeft();
		player2->tankAnimation->runBackward();
	}

	if (this->keyState[SDLK_RIGHT]){
		if(!player2->tank->outOfScreen()){
			player2->tank->moveRight();
			player2->tankAnimation->runForward();
		}
	}

	if (this->keyState[SDLK_KP3]){
		tank2->fire();
	}

}

void Application::update(){
	
	static float lastTime = SDL_GetTicks() / 1000.0f;
	static float windDelay = WIND_DELAY;
	
	float timeSinceLastTime = (SDL_GetTicks() / 1000.0f) - lastTime;

	windDelay -= timeSinceLastTime;

	if(windDelay <= 0){
		wind = (rand() % 7 + 1) - 4;
	}

	lastTime = SDL_GetTicks() / 1000.0f;

	Object::updateAll(timeSinceLastTime);

	if(player1->tank->isDead()){
		player1->tank->setPositionY(0); 
	}
	if(player2->tank->isDead()){
		player2->tank->setPositionY(0); 
	}
}

void Application::execute(){

	while(this->isRunning){
		this->handleEvents();
		this->handleInput();		
		this->update();
		this->render();
		SDL_Delay(2);
	}
}

void Application::render(){
	background->draw(0,0);
	Object::renderAll();
	SDL_Flip(displaySurface);
}



