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

	virtual SDL_Rect getBounds();

	virtual void update(float timeSinceLastTime);	

	void lock();

	unsigned int getAlpha(int x, int y);

	void unlock();
	SDL_Surface *displaySurface;
protected:
	
	SDL_Surface *surface;

	unsigned int width;
	unsigned int height;
};

#endif