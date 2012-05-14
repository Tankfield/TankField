#include <algorithm>
#include "Object.h"
#include "Globals.h"

vector<Object*> Object::allObjects;

Object::Object(Texture *texture, Vector2D pos = Vector2D(0,0))
	: velocity(0,0), speed(300), dead(false) {
	this->texture = texture;
	this->position = pos;

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

void Object::update(float timeSinceLastTime){
	position += velocity * timeSinceLastTime;

	texture->update(timeSinceLastTime);
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

void Object::removeDead()
{
	for (vector<Object*>::iterator it = allObjects.begin(); it != allObjects.end();){
		if ((*it)->dead){
			delete *it;

			it = allObjects.erase(it);
		}
		else{
			it++;
		}
	}
}

void Object::updateAll(float timeSinceLastTime) {
	for (vector<Object*>::iterator it = allObjects.begin(); it != allObjects.end(); it++){
		(*it)->update(timeSinceLastTime);

		for (vector<Object*>::iterator it2 = allObjects.begin(); it2 != allObjects.end(); it2++) {
			if (it != it2) {
				if ((*it)->checkCollision(*it2)) {
					(*it)->onCollision(*it2);
					(*it2)->onCollision(*it);
				}
			}
		}
	}

	Object::removeDead();
}

void Object::renderAll() {
	for (vector<Object*>::iterator it = allObjects.begin(); it != allObjects.end(); it++){
		(*it)->render();
	}
}

void Object::deleteAll() {
	for (vector<Object*>::iterator it = allObjects.begin(); it != allObjects.end(); it++)	{
		delete (*it);
	}

	allObjects.clear();
}

bool Object::outOfScreen()
{
	if (position.x + texture->getWidth() < 0 || position.x > WINDOW_WIDTH || position.y > WINDOW_HEIGHT) {
			return true;
	}
	return false;
}

SDL_Rect Object::getTextureIntersection(SDL_Rect objectIntersection) {
	SDL_Rect textureBounds = texture->getBounds();

	SDL_Rect textureIntersection;

	textureIntersection.x = textureBounds.x + ((int)(objectIntersection.x - position.x) % texture->getWidth());
	textureIntersection.y = textureBounds.y + ((int)(objectIntersection.y - position.y) % texture->getHeight());
	textureIntersection.w = objectIntersection.w - (objectIntersection.x - textureIntersection.x);
	textureIntersection.h = objectIntersection.h - (objectIntersection.y - textureIntersection.y);

	return textureIntersection;
}

bool Object::checkCollision(Object *object) {
	#define MIN(x, y) (x < y) ? x : y
	#define MAX(x, y) (x > y) ? x : y

	SDL_Rect intersectionRect;
	int x2, y2;

	intersectionRect.x = MAX(position.x, object->position.x);
	intersectionRect.y = MAX(position.y, object->position.y);

	x2 = MIN(position.x + texture->getBounds().w, object->position.x + object->texture->getBounds().w);
	y2 = MIN(position.y + texture->getBounds().h, object->position.y + object->texture->getBounds().h);	
	
	if ((x2 - intersectionRect.x > 0) && (y2 - intersectionRect.y > 0)) {		
		intersectionRect.w = x2 - intersectionRect.x;
		intersectionRect.h = y2 - intersectionRect.y;
	}
	else {
		return false;
	}
	
	SDL_Rect textureAIntersection = getTextureIntersection(intersectionRect);
	SDL_Rect textureBIntersection = object->getTextureIntersection(intersectionRect);
	
	int threshold = 200;

	for (int y = 0; y < intersectionRect.h; y++) {
		for (int x = 0; x < intersectionRect.w; x++) {
			if ((texture->getAlpha(textureAIntersection.x + x, textureAIntersection.y + y) > threshold) && (object->getTexture()->getAlpha(textureBIntersection.x + x, textureBIntersection.y + y > threshold))) {
 				return true;
			}
		}
	}		

	return false;
}

void Object::onCollision(Object *object) {

}
