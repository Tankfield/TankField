#include "Ground.h"


Ground::Ground(SDL_Surface* screen) : Texture(getGround(), screen){
}

const char* Ground::getGround(){
	return "textures/ground.png"; 
}