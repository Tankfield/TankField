#include "Terrain.h"


Terrain::Terrain(SDL_Surface* screen) : Object(new Texture(getTerrain(), screen), Vector2D(200,200)){
}

void Terrain::reloadTexture(){
	this->texture->reloadTexture(getTerrain());
}

void Terrain::brake(unsigned int x, unsigned int y) {
	texture->drawCircle(x, y, 35, 0, 255, 0, 0);
}

const char* Terrain::getTerrain(){

	int n;
	srand(time(NULL));
	n=0;
	switch(n){
		case 0:
			return "textures/hill.png"; 
			break;
		case 1:
			return "textures/hill1.png"; 
			break;
		case 2:
			return "textures/hill2.png";
			break;
		case 3:
			return "textures/hill3.png";
			break;
		case 4:
			return "textures/hill4.png";
			break;
	}
}
