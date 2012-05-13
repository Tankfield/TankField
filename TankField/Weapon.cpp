#include "Weapon.h"

Weapon::Weapon(Texture* texture, Vector2D pos) : Object(texture) {
	this->position = pos;
}

Weapon::Weapon(Texture* texture) : Object(texture) 
{}

void Weapon::fireMissile(Vector2D pos){
	new Missile(missileTexture, missileVelocity, pos);
}