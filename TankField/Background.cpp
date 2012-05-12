#include "Background.h"


Background::Background(SDL_Surface* screen) : Texture(getBackground(), screen){
}

const char* Background::getBackground(){

	int n;
	srand(time(NULL));
	n=rand() %3;
	switch(n){
		case 0:
			return "textures/background.png"; 
			break;
		case 1:
			return "textures/background1.png"; 
			break;
		case 2:
			return "textures/background2.png";
			break;
	}
}