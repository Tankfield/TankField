#include "Weapon.h"
#include "Globals.h"


Weapon::Weapon(Texture* texture, int weaponDegrees) : Object(texture, Vector2D(0,0)), degrees(weaponDegrees)
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
	if((!firedMissile)){
		Texture *missileTextureCopy = new Texture(*missileTexture);
 		new Missile(missileTextureCopy, missileVelocity, Vector2D(position.x + 40, position.y + 28));
		toChangeTurn = true;
	}
}
//FIXXXXXX
void Weapon::update(float timeSinceLastTime){

	texture->update(timeSinceLastTime);
	missileVelocity = Vector2D(degrees);
}

void Weapon::onCollision(Object *object){
	//TO DO: collision with terrain!
} 