#include "Ground.h"


Ground::Ground(SDL_Surface* screen) : Object(new Texture(getGround(), screen)){
	position = Vector2D(0,500);
}

const char* Ground::getGround(){
	return "textures/ground.png"; 
}