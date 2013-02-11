#include "Mouse.h"

Mouse::Mouse(SDL_Surface* screen, char* texture) : Object(new Texture(texture, screen), Vector2D(0,0)){
	toCheckCollision = false;
	toRender = false;
}

void Mouse::render(int x, int y){
	this->texture->draw((int)x,(int)y);
}