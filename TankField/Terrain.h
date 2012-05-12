#ifndef _Terrain_H
#define _Terrain_H
#include "Texture.h"
#include <SDL\SDL.h>
#include <time.h>

class Terrain : public Texture{
	static const char* getTerrain();
	
public:
	Terrain(SDL_Surface* screen);
};
#endif