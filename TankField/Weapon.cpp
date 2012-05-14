#include "Weapon.h"


Weapon::Weapon(Texture* texture, int weaponDegrees) : Object(texture, Vector2D(0,0)), firedMissile(false), degrees(weaponDegrees)
{}


int Weapon::getDegrees(){
	return degrees;
}
void Weapon::incDegrees(){
	degrees += 10;
	missileVelocity = Vector2D(degrees);
}
void Weapon::decDegrees(){
	degrees -= 10;                           
	missileVelocity = Vector2D(degrees);
}

void Weapon::fireMissile(){
	if(!firedMissile){
		Texture *missileTextureCopy = new Texture(*missileTexture);
 		new Missile(missileTextureCopy, missileVelocity, Vector2D(position.x + 40, position.y + 20));
		firedMissile = true;
		missileDelay = 0.5;
	}
}

void Weapon::update(float timeSinceLastTime){

	texture->update(timeSinceLastTime);

	if(firedMissile){
		missileDelay -= timeSinceLastTime;
	}

	if (missileDelay < 0){
		firedMissile = false;
		missileDelay = 5;
		missileVelocity = Vector2D(degrees);
	}
}

void Weapon::onCollision(Object *object)
{
} 