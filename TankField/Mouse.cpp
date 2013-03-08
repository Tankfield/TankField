#include "Mouse.h"

Mouse::Mouse(SDL_Surface* screen, char* texture) : Object(new Texture(texture, screen), Vector2D(0,0)){
	toCheckCollision = false;
	toRender = false;
}

void Mouse::render(){
	this->texture->draw((int)this->position.x, (int)this->position.y);
}