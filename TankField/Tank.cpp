#include "Tank.h"

Tank::Tank(Texture* texture, Weapon* weapon) : Object(texture) {
	this->weapon = weapon;
}

void Tank::update(){

	static float lastTime = SDL_GetTicks() / 1000.0f;

	float timeSinceLastTime = (SDL_GetTicks() / 1000.0f) - lastTime;

	position += velocity * timeSinceLastTime;

	texture->update();

	weapon->setPositionX((this->position.x + 50));
	weapon->setPositionY((this->position.y - 55));

	lastTime = SDL_GetTicks() / 1000.0f;
}

void Tank::render(){
	this->texture->draw((int)this->position.x,(int)this->position.y);
	weapon->getTexture()->draw((int)weapon->getPositionX(),(int)weapon->getPositionY());
}

void Tank::fire(){
	this->weapon->fireMissile(Vector2D(weapon->getPositionX() + 20, weapon->getPositionY() + 20));
}