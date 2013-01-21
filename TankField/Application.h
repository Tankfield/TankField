
#ifndef _Applicaiton_H
#define _Application_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Object.h"
#include "Background.h"
#include "Animation.h"
#include "Tank.h"
#include "Weapon.h"
#include "Vector2D.h"
#include "Terrain.h"
#include "Ground.h"
#include "Missile.h"
#include "Player.h"
#include "Server.h"
#include "Client.h"

class Application{

private:
	
	Background* background;
	Terrain* terrain;
	Ground* ground;
	
	TTF_Font *font;
	SDL_Color textColor;
	bool isRunning;

	SDL_Event event;

	SDL_Surface *displaySurface;
	SDL_Surface *displayText;

	void loadContent();
	bool initialize();
	void handleEvents();
	void handleInput();
	void render();
	void update();
	void reset();
	void showText(int x, int y, SDL_Surface* source, SDL_Surface* destination);
	void changeTurn();

	Tank *tank1;
	Tank *tank2;
	Player *player1;
	Player *player2;
	Animation *tankAnimation1;
	Animation *tankAnimation2;
	Animation *weaponAnimation1;
	Animation *weaponAnimation2;
	Weapon* weapon1;
	Weapon* weapon2;
	Server* server;
	Client* client;

	bool keyState[322];
	char buffer [33];

public:


	Application();
	~Application();

	void execute();

};

#endif