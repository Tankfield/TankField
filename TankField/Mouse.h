#ifndef _Mouse_H
#define _Mouse_H

#include "Object.h"


class Mouse : public Object{
private:

public:
	Mouse(SDL_Surface* screen, char* texture);
	
	virtual void render();

	
};

#endif