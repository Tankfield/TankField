#include "Weapon.h"

Weapon::Weapon(Texture* texture, Vector2D pos) : Object(texture) {
	this->position = pos;
}

Weapon::Weapon(Texture* texture) : Object(texture) 
{}
