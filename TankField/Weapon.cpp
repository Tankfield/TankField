#include "Weapon.h"
#include "Globals.h"


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
 		new Missile(missileTextureCopy, missileVelocity, Vector2D(position.x + 40, position.y + 28));
		firedMissile = true;
		missileDelay = MISSILE_DELAY;
	}
}

void Weapon::update(float timeSinceLastTime){

	texture->update(timeSinceLastTime);

	if(firedMissile){
		missileDelay -= timeSinceLastTime;
	}

	if (missileDelay < 0){
		firedMissile = false;
		missileDelay = MISSILE_DELAY;
		missileVelocity = Vector2D(degrees);
	}
}

void Weapon::onCollision(Object *object)
{
} 