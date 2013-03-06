#ifndef _Bot_H
#define _Bot_H

#include "Player.h"
#include "Globals.h"

class Bot : public Player{
private:
	void move();
	void aim();
	void fire();

public:
	Bot(Tank *tank, Animation *tankAnimation, Animation *weaponAnimation);
	~Bot();

	void takeTurn();
	
};


#endif