#include "Object.h"

Object::Object(Texture *texture)
	: direction(0,0), speed(500) {
	this->texture = texture;
	this->position.x = 500;
	this->position.y = 200;
}


void Object::moveUp(){
	//position += Vector2D(0, -1);
	direction = Vector2D(0, -1);
}
void Object::moveDown(){
	//position += Vector2D(0, 1);
	direction = Vector2D(0, 1);
}
void Object::moveLeft(){
	//position += Vector2D(-1, 0);
	direction = Vector2D(-1, 0);
}
void Object::moveRight(){
	//position += Vector2D(1, 0);
	direction = Vector2D(1, 0);
}

void Object::stop(){
	direction = Vector2D(0, 0);
}

void Object::update(){
	static float lastTime = SDL_GetTicks() / 1000.0f;

	float timeSinceLastTime = (SDL_GetTicks() / 1000.0f) - lastTime;

	position += direction * (timeSinceLastTime * speed);

	texture->update();

	lastTime = SDL_GetTicks() / 1000.0f;
}

void Object::render(){
	texture->drawTexture((int)this->position.x,(int)this->position.y);
}

