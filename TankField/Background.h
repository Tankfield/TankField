#ifndef _Background_H
#define _Background_H
#include "Texture.h"
#include <SDL\SDL.h>


class Background : public Texture{
	static const char* getBackground();

public:
	Background(SDL_Surface* screen);

};
#endif