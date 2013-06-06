#ifndef _Terrain_H
#define _Terrain_H
#include "Object.h"
#include <SDL\SDL.h>
#include <time.h>

class Terrain : public Object {
	static const char* getTerrain();
	
public:
	Terrain(SDL_Surface* screen);

	void brake(unsigned int x, unsigned int y);
};
#endif