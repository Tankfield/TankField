#include "Background.h"


Background::Background(SDL_Surface* screen) : Texture(getBackground(), screen){
}

const char* Background::getBackground(){

	//TO ADD - random background generator
	return "background.png";
}