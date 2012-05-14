#ifndef _Player_H
#define _Player_H

#include "Tank.h"

class Player{

private:
	int health;

public:
	Tank *tank;

	Player(Tank *tank);
};


#endif
