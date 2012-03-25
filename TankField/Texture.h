#ifndef _Texture_H
#define _Texture_H

#include <SDL\SDL.h>
#include <SDL\SDL_image.h>



class Texture{
	SDL_Surface* loadImage(const char *filename);
	SDL_Surface *surface;
	unsigned int width;
	unsigned int height;
	

public:
	Texture(const char* filename, SDL_Surface *screen);
	~Texture();

	virtual void drawTexture(int x, int y);

	unsigned int getWidth();
	unsigned int getHeight();

protected:
	SDL_Surface *displaySurface;
};
#endif