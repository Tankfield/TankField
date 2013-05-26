#ifndef _Bot_H
#define _Bot_H

#include "Player.h"
#include "Globals.h"

class Bot : public Player{
private:
	void move();
	void aim(int difference);
	void fire();
	int difference;
	bool moveRight;
	bool moveLeft;
	bool incDegrees;
	bool decDegrees;

public:
	Bot(Tank *tank, Animation *tankAnimation, Animation *weaponAnimation);
	~Bot();

	bool toMoveRight();
	bool toMoveLeft();
	bool toIncDegrees();
	bool toDecDegrees();
	void clearFlags();

	void takeTurn(int enemyPosition);
	
};


#endif