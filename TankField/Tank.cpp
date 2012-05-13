#include "Tank.h"

Tank::Tank(Texture* texture, Weapon* weapon) : Object(texture) {
	this->weapon = weapon;
}

void Tank::update(){

	static float lastTime = SDL_GetTicks() / 1000.0f;

	float timeSinceLastTime = (SDL_GetTicks() / 1000.0f) - lastTime;

	position += velocity * timeSinceLastTime;

	texture->update();

	weapon->position.x = this->position.x + 50;
	weapon->position.y = this->position.y - 55;

	lastTime = SDL_GetTicks() / 1000.0f;
}

void Tank::render(){
	this->texture->draw((int)this->position.x,(int)this->position.y);
	weapon->texture->draw((int)weapon->position.x,(int)weapon->position.y);
}

void Tank::fire(){
	this->weapon->fireMissile(Vector2D(weapon->position.x + 20, weapon->position.y + 20));
}