#include "Button.h"

Button::Button(SDL_Surface* screen, char* texture, Vector2D position) : Object(new Texture(texture, screen), position){
	toRender = false;
	toCheckCollision = false;
	pressed = false;
}


void Button::render(){
	this->texture->draw((int)this->position.x,(int)this->position.y);
}

bool Button::isPressed(){
	return pressed;
}