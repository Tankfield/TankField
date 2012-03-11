#include "Texture.h"



Texture::Texture(const char* filename, SDL_Surface *screen)
: displaySurface(screen) {
	this->surface = this->loadImage(filename);

	this->width = this->surface->w;
	this->height = this->surface->h;
};


Texture::~Texture(){
	SDL_FreeSurface(surface);
}

SDL_Surface* Texture::loadImage(const char *filename){
	return (SDL_DisplayFormatAlpha(IMG_Load(filename)));
}

void Texture::draw(int x, int y){
	SDL_Rect tempRect;
	tempRect.x = x;
	tempRect.y = y;
	SDL_BlitSurface(surface, NULL, displaySurface, &tempRect);
}

unsigned int Texture::getWidth(){
	return width;
}
unsigned int Texture::getHeight(){
	return height;
}