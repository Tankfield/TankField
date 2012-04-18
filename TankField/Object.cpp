#include "Object.h"

Object::Object(Texture *texture){
	this->texture = texture;
	this->position.x = 500;
	this->position.y = 200;
}


void Object::moveUp(){
	position += Vector2D(0, -1);
}
void Object::moveDown(){
	position += Vector2D(0, 1);
}
void Object::moveLeft(){
	position += Vector2D(-1, 0);
}
void Object::moveRight(){
	position += Vector2D(1, 0);
}



void Object::render(){
	texture->drawTexture((int)this->position.x,(int)this->position.y);
}

