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
	SDL_FreeSurface(displayText);
	
    TTF_CloseFont(font);

    TTF_Quit();

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
	tank1 = new Tank(tankAnimation1, weapon1, Vector2D(TANK1_POS_X,TANK1_POS_Y), Vector2D(TANK1_WEAPON_POS_X,TANK1_WEAPON_POS_Y));
	tankAnimation2 = new Animation("textures/redtank.png", displaySurface, 4, 5, 30);
	tank2 = new Tank(tankAnimation2, weapon2, Vector2D(TANK2_POS_X,TANK2_POS_Y), Vector2D(TANK2_WEAPON_POS_X,TANK2_WEAPON_POS_Y));
	player1 = new Player(tank1, tankAnimation1, weaponAnimation1);
	player2 = new Player(tank2, tankAnimation2, weaponAnimation2);	
	if (isServer)
		server = new Server(3000);
	if (isClient)
		client = new Client(HOST_IP, 3000);
}

bool Application::initialize(){
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		this->displaySurface = NULL;
		return false;
	}
	SDL_WM_SetIcon(SDL_LoadBMP("icon.bmp"), NULL);
	SDL_WM_SetCaption("TankField", NULL);
	this->displaySurface = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT , 32, SDL_SWSURFACE);


	if(SDLNet_Init() < 0){
		return false;
	}
	
	loadContent();

	if(this->displaySurface == NULL){
		return false;
	}

	if(TTF_Init() == -1){
        return false;
    }

	font = TTF_OpenFont("arial.ttf", 40);

	SDL_Color textColor ={0, 0, 0};
	
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
	if((singlePlayer && player1Turn) || (isServer && player1Turn)){
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
			if(!this->keyState[SDLK_d]){
				if(!player1->tank->outOfScreen()){
					player1->tank->moveLeft();
					player1->tankAnimation->runBackward();
				}
			}
		}

		if (this->keyState[SDLK_d]){
			if(!this->keyState[SDLK_a]){
				player1->tank->moveRight();
				player1->tankAnimation->runForward();
			}
		}

		if (this->keyState[SDLK_SPACE]){
			tank1->fire();
			firedMissile = true;
		}
	}
	//player2 controls
	if((singlePlayer && player2Turn) || (isClient && player2Turn)){
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
			if(!this->keyState[SDLK_RIGHT]){
				player2->tank->moveLeft();
				player2->tankAnimation->runBackward();
			}
		}

		if (this->keyState[SDLK_RIGHT]){
			if(!this->keyState[SDLK_LEFT]){
				if(!player2->tank->outOfScreen()){
					player2->tank->moveRight();
					player2->tankAnimation->runForward();
				}
			}
		}

		if (this->keyState[SDLK_KP3]){
			tank2->fire();
			firedMissile = true;
		}
	}
	//resets
	if (this->keyState[SDLK_r]){
		reset();
	}

}

void Application::update(){
	
	static float lastTime = SDL_GetTicks() / 1000.0f;
	static float windDelay = WIND_DELAY;
	
	float timeSinceLastTime = (SDL_GetTicks() / 1000.0f) - lastTime;
	if(isServer && player1Turn){
		if (server->clientConnected()) {	
			int buffer4[2];
			if (server->receiveData(&buffer4, sizeof(buffer))) {
				if((buffer4[0] == 100) && (buffer4[1] == 200)){
					player1->tank->setPositionY(player1->tank->getPositionY() - 0.1);
				}
			}

			int buffer3[2];
			buffer3[0] = 100;
			buffer3[1] = 200;
			server->sendData(&buffer3, sizeof(buffer3));

		}
	}
	else if(isClient && player2Turn){
		int buffer2[2];
		buffer2[0] = 100;
		buffer2[1] = 200;
		client->sendData(&buffer2, sizeof(buffer2));

		int buffer[2];
		if (client->receiveData(&buffer, sizeof(buffer))){
			if((buffer[0] == 100) && (buffer[1] == 200)){
				player2->tank->setPositionY(player2->tank->getPositionY() - 0.1);
			}
		}
	}

	if(toChangeTurn){
		changeTurn();
	}

	lastTime = SDL_GetTicks() / 1000.0f;

	Object::updateAll(timeSinceLastTime);
	

	//tanks go in the sky when dead :D
	//if(player1->tank->isDead()){
	//	player1->tank->setPositionY(0); 
	//}
	//if(player2->tank->isDead()){
	//	player2->tank->setPositionY(0); 
	//}
}

void Application::reset(){
	tank1->setHealth(5);
	tank2->setHealth(5);
	tank1->setPositionX(TANK1_POS_X);
	tank1->setPositionY(TANK1_POS_Y);
	tank2->setPositionX(TANK2_POS_X);
	tank2->setPositionY(TANK2_POS_Y);
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
	//player2
	itoa(player1->tank->getHealth(),buffer,10);
	displayText = TTF_RenderText_Solid(font, buffer, textColor);
	showText(20, 20, displayText, displaySurface);
	//player2
	itoa(player2->tank->getHealth(),buffer,10);
	displayText = TTF_RenderText_Solid(font, buffer, textColor);
	showText(1170, 20, displayText, displaySurface);
	//wind
	itoa(wind,buffer,10);
	displayText = TTF_RenderText_Solid(font, buffer, textColor);
	showText(600, 150, displayText, displaySurface);

	Object::renderAll();
	SDL_Flip(displaySurface);
	
}

void Application::showText( int x, int y, SDL_Surface* source, SDL_Surface* destination){
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source, NULL, destination, &offset);
}

void Application::changeTurn(){
	if(player1Turn){
		player1Turn = false;
		player2Turn = true;

		toChangeTurn = false;
		changeWind();
		firedMissile = false;
	}
	else if(player2Turn){
		player2Turn = false;
		player1Turn = true;

		toChangeTurn = false;
		changeWind();
		firedMissile = false;
	}
}

void Application::changeWind(){
	wind = (rand() % 7 + 1) - 4;
}

