#include "Object.h"

Object::Object(Texture *texture){
	this->texture = texture;
	y = 0;
	x = 0;
}

float Object::getX() const {
	return x;
}
float Object::getY() const {
	return y;
}

void Object::moveLeft(){
	x-=10;
}

void Object::moveRight(){
	x+=10;
}

void Object::render(){
	texture->drawTexture((int)x,(int)y);
}