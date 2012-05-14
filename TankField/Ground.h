#ifndef _Ground_H
#define _Ground_H
#include "Object.h"
#include <SDL\SDL.h>

class Ground : public Object {
	static const char* getGround();
	
public:
	Ground(SDL_Surface* screen);
};
#endif