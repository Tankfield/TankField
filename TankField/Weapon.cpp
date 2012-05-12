#include "Weapon.h"

Weapon::Weapon(Texture* texture, Vector2D pos) : Object()
{
	this->texture = texture;
	this->position = pos;
}

Weapon::Weapon(Texture* texture){
	this->texture = texture;
};

Weapon::Weapon(){};