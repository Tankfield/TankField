#ifndef _Menu_H
#define _Menu_H

#include <SDL/SDL.h>
#include "Object.h"

class Menu : public Object{
private:


public:	
	Menu(SDL_Surface* screen, char* texutre);

	virtual void render();
};



#endif