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
	if(this->displayText != NULL){
		//SDL_FreeSurface(displayText);
	}
	
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
	greenWinner = new Texture("textures/gwin.png",displaySurface);
	redWinner = new Texture("textures/rwin.png",displaySurface);	
	
	/*if (isServer) {
		server = new Server(3000);
		while(!server->clientConnected()) { SDL_Delay(100); }
	}	

	if (isClient)
		client = new Client(HOST_IP, 3000);*/
}

void Application::loadMenuContent(){
	menu = new Menu(displaySurface, "textures/gui/gui.png");
	botGameButton = new Button(displaySurface, "textures/gui/botgame.png", Vector2D(BOTGAME_BUTTON_POS_X, BOTGAME_BUTTON_POS_Y));
	versusButton = new Button(displaySurface, "textures/gui/versus.png", Vector2D(VERSUS_BUTTON_POS_X, VERSUS_BUTTON_POS_Y));
	createGameButton = new Button(displaySurface, "textures/gui/create.png", Vector2D(CREATE_GAME_BUTTON_POS_X, CREATE_GAME_BUTTON_POS_Y));
	joinGameButton = new Button(displaySurface, "textures/gui/join.png", Vector2D(JOIN_GAME_BUTTON_POS_X, JOIN_GAME_BUTTON_POS_Y));
	exitGameButton = new Button(displaySurface, "textures/gui/exit.png", Vector2D(EXIT_BUTTON_POS_X, EXIT_BUTTON_POS_Y));
	mouse = new Mouse(displaySurface, "textures/gui/mouse.png");
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
	loadMenuContent();

	menu->invertToCheckCollisionAll();
	menu->setToCheckCollision(false);

	SDL_ShowCursor(0);
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
	leftMouseButton = false;
	showMenu = true;

	server = NULL;
	client = NULL;
	player2 = NULL;
	dummyBot = NULL;

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
		case SDL_MOUSEBUTTONDOWN:
			if(event.button.button == SDL_BUTTON_LEFT){
				leftMouseButton = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if(event.button.button == SDL_BUTTON_LEFT){
				leftMouseButton = false;
			}
			break;
		}
	}
}

void Application::handleInput(){
	static bool escButton = false;
	player1->stop();
	if(player2 != NULL){
		player2->stop();
	}
	if(dummyBot != NULL){
		dummyBot->stop();
	}

	if(showMenu && !inGame){
	
	}

	if (keyState[SDLK_ESCAPE]) {
		escButton = true;
	}
	else if(escButton){
		if(inGame){
			
		}
		else if((!inGame && isServer) || (!inGame && isClient) || (!inGame && isVersus)){
		
		}
		showMenu = !showMenu;
		escButton = false;
		menu->invertToCheckCollisionAll();
		menu->setToCheckCollision(false);
	}

	if(showMenu){
		handleMouseEvents();
	}
	

	//player1 controls
	if((isVersus && player1Turn) || (isServer && player1Turn) || (isBotGame && player1Turn)){
		handlePlayer1Input(keyState[SDLK_a], keyState[SDLK_d], keyState[SDLK_w], keyState[SDLK_s], keyState[SDLK_SPACE]);
	}
	//player2 controls
	if((isVersus && player2Turn) || (isClient && player2Turn)){
		handlePlayer2Input(keyState[SDLK_LEFT], keyState[SDLK_RIGHT], keyState[SDLK_UP], keyState[SDLK_DOWN], keyState[SDLK_KP3]);
	}
	//bot game
	if(isBotGame && player2Turn){
		dummyBot->takeTurn(player1->tank->getPositionX());
		//increasing = false;
		//decreasing = false;
		if(dummyBot->toMoveLeft()){
			if(!player2->tank->isBlocking()){
				player2->tank->moveLeft();
				player2->tankAnimation->runBackward();
			}
		}
		if(dummyBot->toMoveRight()){
			if(!player2->tank->outOfScreen()){
				player2->tank->moveRight();
				player2->tankAnimation->runForward();
			}
		}
		
		if(increasing){
			if(player2->tank->weapon->getDegrees() < 65){
				player2->tank->weapon->incDegrees();
				player2->weaponAnimation->runForward();
			}
			increasing = false;
		}
		else if(dummyBot->toIncDegrees()){
			increasing = true;
		}
		
		else if(decreasing){
			if(player2->tank->weapon->getDegrees() > -65){
				player2->tank->weapon->decDegrees();
				player2->weaponAnimation->runBackward();
			}
			decreasing = false;
		}
		else if(dummyBot->toDecDegrees()){
			decreasing = true;
		}
		dummyBot->clearFlags();
	}
	//reset
	if(!isClient && (isServer && !player2Turn)){
		if (this->keyState[SDLK_r]){
			reset();
			if(isServer){
				setResetIsPressed(true);
				server->sendData(&resetIsPressed, PACKET_SIZE);
			}
		}
	}
}

void Application::handleMouseEvents(){
	if(leftMouseButton){
		if(createGameButton->isPressed()){
			setGameMode(1);
		}
		else if(joinGameButton->isPressed()){
			setGameMode(2);
		}
		else if(versusButton->isPressed()){
			setGameMode(3);
		}
		else if(botGameButton->isPressed()){
			setGameMode(4);
		}
		else if(exitGameButton->isPressed()){
			this->isRunning = false;
		}
	}
	botGameButton->setPressed(false);
	versusButton->setPressed(false);
	createGameButton->setPressed(false);
	joinGameButton->setPressed(false);
	exitGameButton->setPressed(false);
}

void Application::handlePlayer1Input(bool leftButton, bool rightButton, bool upButton, bool downButton, bool fireButton){
	static bool wPressed = false;
	static bool sPressed = false;
	static bool sendButtonS = false;
	static bool sendButtonW = false;
	if (upButton){
			wPressed = true;
		}
	else if(wPressed){
		if(player1->tank->weapon->getDegrees() > -65){
			player1->tank->weapon->decDegrees();
			player1->weaponAnimation->runForward();
			sendButtonW = true;
		}
		wPressed = false;
	}


	if (downButton){
		sPressed = true;
	}
	else if(sPressed) {
		if(player1->tank->weapon->getDegrees() < 75){
			player1->tank->weapon->incDegrees();
			player1->weaponAnimation->runBackward();
			sendButtonS = true;
		}
		sPressed = false;
	}


		
	if (leftButton){
		if(!rightButton){
			if(!player1->tank->outOfScreen()){
				player1->tank->moveLeft();
				player1->tankAnimation->runBackward();
			}
		}
	}

	if (rightButton){
		if(!leftButton){
			if(!player1->tank->isBlocking()){
				player1->tank->moveRight();
				player1->tankAnimation->runForward();
			}
		}
	}

	if (fireButton){
		tank1->fire();
		firedMissile = true;
	}


	//NETWORKING
	if(server != NULL){
		//sending info
		if(isServer && player1Turn){
			//sending if tank has moved
			if(leftButton || rightButton){
				setXPosition(player1->tank->getPositionX());
				server->sendData(&xPosition, PACKET_SIZE);
			}
			//sending if weapon has moved
			if(sendButtonS){
				setDownIsPressed(sendButtonS);
				server->sendData(&downIsPressed, PACKET_SIZE);
				sendButtonS = false;
			}
			if(sendButtonW){
				setUpIsPressed(sendButtonW);
				server->sendData(&upIsPressed, PACKET_SIZE);
				sendButtonW = false;
			}
			//sending if fired a missile
			if(fireButton){
				setFirePressed(fireButton);
				server->sendData(&firePressed, PACKET_SIZE);
			}
		}
	}
}

void Application::handlePlayer2Input(bool leftButton, bool rightButton, bool upButton, bool downButton, bool fireButton){
	
	static bool downPressed = false;
	static bool upPressed = false;
	static bool sendButtonUp = false;
	static bool sendButtonDown = false;
	
	if (downButton){
		downPressed = true;
	}
	else if(downPressed){
		if(player2->tank->weapon->getDegrees() > -75){
			player2->tank->weapon->decDegrees();
			player2->weaponAnimation->runBackward();
			sendButtonDown = true;
		}
		downPressed = false;
	}


	if (upButton){
		upPressed = true;
	}
	else if(upPressed){
		if(player2->tank->weapon->getDegrees() < 65){
			player2->tank->weapon->incDegrees();
			player2->weaponAnimation->runForward();
			sendButtonUp = true;
		}
		upPressed = false;
	}


	if (leftButton){
		if(!rightButton){
			if(!player2->tank->isBlocking()){
				player2->tank->moveLeft();
				player2->tankAnimation->runBackward();
			}
		}
	}

	
	if (rightButton){
		if(!leftButton){
			if(!player2->tank->outOfScreen()){
				player2->tank->moveRight();
				player2->tankAnimation->runForward();
			}
		}
	}

	if (fireButton){
		tank2->fire();
		firedMissile = true;
	}
	//NETWORKING
	if(client != NULL){
		//sending info
		if(isClient && player2Turn){
			//sending if tank has moved
			if(leftButton || rightButton){
				setXPosition(player2->tank->getPositionX());
				client->sendData(&xPosition, PACKET_SIZE);
			}
			//sending if weapon has moved
			if(sendButtonDown){
				setDownIsPressed(sendButtonDown);
				client->sendData(&downIsPressed, PACKET_SIZE);
				sendButtonDown = false;
			}
			if(sendButtonUp){
				setUpIsPressed(sendButtonUp);
				client->sendData(&upIsPressed, PACKET_SIZE);
				sendButtonUp = false;
			}
			//sending if fired a missile
			if(fireButton){
				setFirePressed(fireButton);
				client->sendData(&firePressed, PACKET_SIZE);
			}
		}
	}
}

void Application::handleReceivedData(){
	static bool goUp = false;
	static bool goDown = false;
	//server part
	if((isServer && player2Turn) && server != NULL){
		if (server->clientConnected()) {	
			if (server->receiveData(&receivedData, PACKET_SIZE)) {
				if(receivedData.type == 1){	
					if(receivedData.data > player2->tank->getPositionX()){
						player2->tank->moveRight();
						player2->tankAnimation->runForward();
					}
					if(receivedData.data < player2->tank->getPositionX()){
						player2->tank->moveLeft();
						player2->tankAnimation->runBackward();
					}
				}
				if(receivedData.type == 2){
					if(receivedData.data){
						tank2->fire();
						firedMissile = true;
					}
				}
				if(receivedData.type == 3){
					if(receivedData.data){
						player2->tank->weapon->incDegrees();
						player2->weaponAnimation->runForward();
					}
				}
				if(receivedData.type == 4){
					if(receivedData.data){
						player2->tank->weapon->decDegrees();
						player2->weaponAnimation->runBackward();
					}
				}
				if(receivedData.type == 5){
					setWind(receivedData.data);
				}
			}		
		}
	}
	//client part
	else if((isClient && player1Turn) && client != NULL){
		if (client->receiveData(&receivedData, PACKET_SIZE)){
			if(receivedData.type == 1){
				if(receivedData.data > player1->tank->getPositionX()){
					player1->tank->moveRight();
					player1->tankAnimation->runForward();
				}
				else if(receivedData.data < player1->tank->getPositionX()){
					player1->tank->moveLeft();
					player1->tankAnimation->runBackward();
				}	
			}
				
			if(receivedData.type == 2){
				if(receivedData.data){
					tank1->fire();
					firedMissile = true;
				}
			}
			if(receivedData.type == 3){
				if(receivedData.data){
					player1->tank->weapon->decDegrees();
					player1->weaponAnimation->runForward();
				}
			}
			if(receivedData.type == 4){
				if(receivedData.data){
					player1->tank->weapon->incDegrees();
					player1->weaponAnimation->runBackward();
				}
			}
			if(receivedData.type == 5){
				setWind(receivedData.data);
			}
			if(receivedData.type == 6){
				if(receivedData.data){
					reset();
				}
			}
		}
	}
}

void Application::update(){
	static float lastTime = SDL_GetTicks() / 1000.0f;
	//static float windDelay = WIND_DELAY;

	float timeSinceLastTime = (SDL_GetTicks() / 1000.0f) - lastTime;
	lastTime = SDL_GetTicks() / 1000.0f;

	if(toChangeTurn){
		changeTurn();
	}
	joinServerOrHostServer();
	if(isBotGame){
		createBot();
	}
	if(!isBotGame){
		createSecondPlayer();
	}
	handleReceivedData();
	Object::updateAll(timeSinceLastTime);
	
}

void Application::reset(){
	tank1->setHealth(5);
	tank2->setHealth(5);
	tank1->setPositionX(TANK1_POS_X);
	tank1->setPositionY(TANK1_POS_Y);
	tank2->setPositionX(TANK2_POS_X);
	tank2->setPositionY(TANK2_POS_Y);
	toChangeTurn = false;
	firedMissile = false;
	player1Turn = true;
	player2Turn = false;
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

	if (showMenu)  {
		menu->render();
		botGameButton->render();
		versusButton->render();
		createGameButton->render();
		joinGameButton->render();
		exitGameButton->render();
		SDL_GetMouseState(&mouseX, &mouseY);
		mouse->setPositionX(mouseX);
		mouse->setPositionY(mouseY);
		mouse->render();
	}
	else {
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
		SDL_Rect rect = {535,100,130,20};
		SDL_FillRect(displaySurface, &rect, 0xFF0000);
		if (wind>=0){ 
			SDL_Rect rect = {600,105,wind*20,10};
			SDL_FillRect(displaySurface, &rect, 0xFFFFFF);
		} else {
			SDL_Rect rect = {600+(wind*20),105,-wind*20,10};
			SDL_FillRect(displaySurface, &rect, 0xFFFFFF);
		}
		//winner
		if (player1->tank->isDead())
			redWinner->draw(340,150);
		else if (player2->tank->isDead())
			greenWinner->draw(330,150);
		
		 
		Object::renderAll();
	}

	SDL_Flip(displaySurface);
	
}

void Application::showText( int x, int y, SDL_Surface* source, SDL_Surface* destination){
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source, NULL, destination, &offset);
}

void Application::changeTurn(){
	if((!player1->tank->isDead()) && (!player2->tank->isDead())){
		if(player1Turn){
			player1Turn = false;
			player2Turn = true;

			toChangeTurn = false;
			if(!isServer){
				changeWind();
				if(isClient){
					setWindData(wind);
					client->sendData(&windData, PACKET_SIZE);
				}
			}
			firedMissile = false;
		}
		else if(player2Turn){
			player2Turn = false;
			player1Turn = true;

			toChangeTurn = false;
			if(!isClient){
				changeWind();
				if(isServer){
					setWindData(wind);
					server->sendData(&windData, PACKET_SIZE);
				}
			}
			firedMissile = false;
		}
	}
}

void Application::changeWind(){
	wind = ((rand() % 7 + 1) - 4);
}

void Application::setWind(int value){
	wind = value;
}

void Application::joinServerOrHostServer(){
	if(isServer) {
		if(server == NULL){
			server = new Server(3000);
			client = NULL;
			while(!server->clientConnected()){ 
				SDL_Delay(100); 
			}
		}
	}	
	else if(isClient){
		if(client == NULL){
			client = new Client(HOST_IP, 3000);
			server = NULL;
		}
	}
}

void Application::setGameMode(int mode){
	switch(mode){
		case 1:
		isClient = false;
		isServer = true;
		isVersus = false;
		isBotGame = false;
		break;

		case 2:
		isClient = true;
		isServer = false;
		isVersus = false;
		isBotGame = false;
		break;

		case 3:
		isClient = false;
		isServer = false;
		isVersus = true;
		isBotGame = false;
		break;

		case 4:
		isClient = false;
		isServer = false;
		isVersus = false;
		isBotGame = true;
		break;
	}
	reset();
	menu->invertToCheckCollisionAll();
	menu->setToCheckCollision(false);
	showMenu = false;
}

void Application::createBot(){
	dummyBot = new Bot(tank2, tankAnimation2, weaponAnimation2);
}

void Application::createSecondPlayer(){
	player2 = new Player(tank2, tankAnimation2, weaponAnimation2);
}

void Application::setXPosition(int data){
	xPosition.type = 1;
	xPosition.data = data;
}

void Application::setFirePressed(int data){
	firePressed.type = 2;
	firePressed.data = data;
}

void Application::setUpIsPressed(int data){
	upIsPressed.type = 3;
	upIsPressed.data = data;
}

void Application::setDownIsPressed(int data){
	downIsPressed.type = 4;
	downIsPressed.data = data;
}

void Application::setWindData(int data){
	windData.type = 5;
	windData.data = data;
}

void Application::setResetIsPressed(int data){
	resetIsPressed.type = 6;
	resetIsPressed.data = data;
}
