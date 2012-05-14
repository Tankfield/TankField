#include "Player.h"

Player::Player(Tank *tank, Animation *tankAnimation, Animation *weaponAnimation){
	this->tank = tank;
	this->tankAnimation = tankAnimation;
	this->weaponAnimation = weaponAnimation;
}

void Player::stop(){
	this->tank->stop();
	this->tankAnimation->stop();
	this->weaponAnimation->stop();
}