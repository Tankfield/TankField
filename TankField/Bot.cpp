#include "Bot.h"

Bot::Bot(Tank *tank, Animation *tankAnimation, Animation *weaponAnimation) : Player(tank, tankAnimation, weaponAnimation)
{}

void Bot::takeTurn(){
	move();
	aim();
	fire();
	firedMissile = true;
}
void Bot::move(){}
void Bot::aim(){
	/*if(this->tank->weapon->getDegrees() < 55){
		
	}*/
}
void Bot::fire(){
	this->tank->fire();
}