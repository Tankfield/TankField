#ifndef _Texture_H
#define _Texture_H

#include <SDL\SDL.h>
#include <SDL\SDL_image.h>



class Texture{
	SDL_Surface* loadImage(const char *filename);


public:
	Texture(const char* filename, SDL_Surface *screen);
	Texture(const Texture &other);
	~Texture();

	virtual void draw(int x, int y);
	unsigned int getWidth();
	unsigned int getHeight();

	virtual void update();

protected:
	SDL_Surface *displaySurface;
	SDL_Surface *surface;
	unsigned int width;
	unsigned int height;
};
#endif