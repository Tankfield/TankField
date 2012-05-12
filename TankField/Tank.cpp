#include "Tank.h"

Tank::Tank(Texture* texture, Weapon weapon) : Object() {
	this->texture = texture;
	this->weapon = weapon;
	this->update();
}

void Tank::update(){

	static float lastTime = SDL_GetTicks() / 1000.0f;

	float timeSinceLastTime = (SDL_GetTicks() / 1000.0f) - lastTime;

	position += velocity * timeSinceLastTime;

	texture->update();

	weapon.position.x = this->position.x + 50;
	weapon.position.y = this->position.y - 55;

	lastTime = SDL_GetTicks() / 1000.0f;
}

void Tank::render(){
	this->texture->drawTexture((int)this->position.x,(int)this->position.y);
	weapon.texture->drawTexture((int)weapon.position.x,(int)weapon.position.y);
}