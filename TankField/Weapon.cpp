#include "Weapon.h"

Weapon::Weapon(Texture* texture, Vector2D pos) : Object(texture), firedMissile(false), degrees(40), missileDelay(3), missileVelocity(40){
	this->position = pos;
}

Weapon::Weapon(Texture* texture) : Object(texture), firedMissile(false), degrees(40)
{}


int Weapon::getDegrees(){
	return degrees;
}
void Weapon::incDegrees(){
	if(degrees < 70){
		degrees += 5;
	}

	missileVelocity = Vector2D(degrees);
}
void Weapon::decDegrees(){
	if(degrees > -70){
		degrees -= 5;
	}
	                             
	missileVelocity = Vector2D(degrees);
}

void Weapon::fireMissile(){
	if(!firedMissile){
		Texture *missileTextureCopy = new Texture(*missileTexture);

 		new Missile(missileTextureCopy, missileVelocity, Vector2D(position.x + 20, position.y + 20));
		firedMissile = true;
		missileDelay = 0.5;
	}
}

void Weapon::update(float timeSinceLastTime){

	if(firedMissile){
		missileDelay -= timeSinceLastTime;
	}


	if (missileDelay < 0){
		firedMissile = false;
		missileDelay = 5;
		missileVelocity = Vector2D(degrees);
	}
}