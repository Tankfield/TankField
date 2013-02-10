#include "Menu.h"

Menu::Menu(SDL_Surface* screen, char* texture) : Object(new Texture(texture, screen), Vector2D(0,0)){
	toRender = false;
	toChechCollision = false;
}

Menu::~Menu(){

}

void Menu::render(){
	this->texture->draw((int)this->position.x,(int)this->position.y);
}