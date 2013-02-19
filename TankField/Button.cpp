#include "Button.h"

Button::Button(SDL_Surface* screen, char* texture, Vector2D position) : Object(new Texture(texture, screen), position){
	toRender = false;
	toCheckCollision = true;
}


void Button::render(){
	this->texture->draw((int)this->position.x,(int)this->position.y);
}

void Button::onCollision(Object *object) {
	if (dynamic_cast<Mouse*>(object) != NULL){
		pressed = true;
	}
	else{
		pressed = false;
	}
}

bool Button::isPressed(){
	return pressed;
}
void Button::setPressed(bool status){
	pressed = status;
}