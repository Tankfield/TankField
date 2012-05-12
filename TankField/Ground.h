#ifndef _Ground_H
#define _Ground_H
#include "Texture.h"
#include <SDL\SDL.h>

class Ground : public Texture{
	static const char* getGround();
	
public:
	Ground(SDL_Surface* screen);
};
#endif