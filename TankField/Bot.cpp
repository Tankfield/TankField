#include "Bot.h"

Bot::Bot(Tank *tank, Animation *tankAnimation, Animation *weaponAnimation) : Player(tank, tankAnimation, weaponAnimation)
{
	moveLeft = false;
	moveRight = false;
	incDegrees = false;
	decDegrees = false;
}

bool Bot::toMoveRight(){
	return moveRight;
}
bool Bot::toMoveLeft(){
	return moveLeft;
}
bool Bot::toIncDegrees(){
	return incDegrees;
}
bool Bot::toDecDegrees(){
	return decDegrees;
}
void Bot::clearFlags(){
	moveLeft = false;
	moveRight = false;
	incDegrees = false;
	decDegrees = false;
}

void Bot::takeTurn(int enemyPosition){
	//move();
	difference = this->tank->getPositionX() - enemyPosition;
	aim(difference);
	
}
void Bot::move(){}
void Bot::aim(int difference){
	//-25
	if((difference <= 900) && (difference >= 800)){
		if(this->tank->weapon->getDegrees() < -25){
			this->incDegrees = true;
		}
		else if(this->tank->weapon->getDegrees() > -25){
			this->decDegrees = true;
		}
		else{
			fire();
		}
	}
	//-35
	else if((difference <= 1070) && (difference >= 1000)){
		if(this->tank->weapon->getDegrees() < -35){
			this->incDegrees = true;
		}
		else if(this->tank->weapon->getDegrees() > -35){
			this->decDegrees = true;
		}
		else{
			fire();
		}
	}
	//-45
	else if((difference < 1100) && (difference >= 1070)){
		if(this->tank->weapon->getDegrees() < -45){
			this->incDegrees = true;
		}
		else if(this->tank->weapon->getDegrees() > -45){
			this->decDegrees = true;
		}
		else{
			fire();
		}
	}
	else if((difference > 1100) || (((difference < 1000) && (difference >= 955)))){
		this->moveLeft = true;
	}
	else if((difference < 800) || (((difference < 940) && (difference > 900)))){
		this->moveRight = true;
	}
	else{
		fire();
	}
}
void Bot::fire(){
	this->tank->fire();
	firedMissile = true;
}