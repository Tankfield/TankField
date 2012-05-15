#ifndef _Player_H
#define _Player_H

#include "Tank.h"
#include "Animation.h"

class Player{


public:
	Tank *tank;
	Animation *tankAnimation;
	Animation *weaponAnimation;

	Player(Tank *tank, Animation *tankAnimation, Animation *weaponAnimation);

	void stop();
};


#endif
