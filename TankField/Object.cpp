#include "Object.h"

vector<Object*> Object::allObjects;

Object::Object(Texture *texture)
	: velocity(0,0), speed(500) {
	this->texture = texture;
	this->position.x = 500;
	this->position.y = 200;

	allObjects.push_back(this);
}

Object::~Object(){
	delete texture;
}


void Object::moveUp(){
	velocity = Vector2D(0, -1) * speed;
}

void Object::moveDown(){
	velocity = Vector2D(0, 1) * speed;
}

void Object::moveLeft(){
	velocity = Vector2D(-1, 0) * speed;
}

void Object::moveRight(){
	velocity = Vector2D(1, 0) * speed;
}

void Object::stop(){
	velocity = Vector2D(0, 0);
}

void Object::update(){
	static float lastTime = SDL_GetTicks() / 1000.0f;

	float timeSinceLastTime = (SDL_GetTicks() / 1000.0f) - lastTime;

	position += velocity * timeSinceLastTime;

	texture->update();

	lastTime = SDL_GetTicks() / 1000.0f;
}

void Object::render(){
	texture->draw((int)this->position.x,(int)this->position.y);
}

float Object::getPositionX(){
	return this->position.x;
}
float Object::getPositionY(){
	return this->position.y;
}
float Object::getVelocityX(){
	return this->velocity.x;
}
float Object::getVelocityY(){
	return this->velocity.y;
}

void Object::setPositionX(float x){
	this->position.x = x;
}
void Object::setPositionY(float y){
	this->position.y = y;
}
void Object::setVelocityX(float x){
	this->velocity.x = x;
}
void Object::setVelocityY(float y){
	this->velocity.y = y;
}

Texture *Object::getTexture(){
	return this->texture;
}



void Object::updateAll() {
	for (vector<Object*>::iterator it = allObjects.begin(); it != allObjects.end(); it++)	{
		(*it)->update();
	}
}

void Object::renderAll() {
	for (vector<Object*>::iterator it = allObjects.begin(); it != allObjects.end(); it++)	{
		(*it)->render();
	}
}

void Object::deleteAll() {
	for (vector<Object*>::iterator it = allObjects.begin(); it != allObjects.end(); it++)	{
		delete (*it);
	}

	allObjects.clear();
}

